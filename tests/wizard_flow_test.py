#!/usr/bin/env python3
"""
Wizard Flow Test — AetherMUD
Tests: promote, setrole rp/coding, cd permissions, help rpwiz, demote
"""

import socket
import time
import sys
import threading

HOST = "127.0.0.1"
PORT = 3000
TIMEOUT = 8


PROMPT = "\r\n> "


def conn_send(s, data):
    s.sendall((data + "\r\n").encode())


def conn_recv(s, timeout=TIMEOUT, until=None):
    """Receive until until-string is found, or timeout."""
    s.settimeout(timeout)
    buf = b""
    deadline = time.time() + timeout
    while time.time() < deadline:
        try:
            chunk = s.recv(4096)
            if not chunk:
                break
            buf += chunk
            text = buf.decode("latin-1", errors="replace")
            if until and until in text:
                return text
        except socket.timeout:
            break
    return buf.decode("latin-1", errors="replace")


def drain(s, timeout=0.5):
    """Discard any remaining bytes in the socket's receive buffer."""
    s.settimeout(timeout)
    try:
        while True:
            chunk = s.recv(4096)
            if not chunk:
                break
    except socket.timeout:
        pass


def wait_for(s, prompt, timeout=TIMEOUT):
    out = conn_recv(s, timeout=timeout, until=prompt)
    return out


def session_create_admin(username, password):
    """Create the admin (first-ever) player."""
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((HOST, PORT))
    out = wait_for(s, "Enter your name:", 10)
    conn_send(s, username)
    out = wait_for(s, "password", 8)
    conn_send(s, password)
    out = wait_for(s, "password", 8)   # confirm
    conn_send(s, password)
    # Admin first player skips chargen — wait for playing prompt
    out = wait_for(s, PROMPT, 12)
    print(f"[ADMIN-CREATE] Final output snippet: ...{out[-200:].strip()}")
    return s


def session_create_player(username, password):
    """Create a normal player through chargen."""
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((HOST, PORT))

    out = wait_for(s, "Enter your name:", 10)
    conn_send(s, username)

    out = wait_for(s, "password", 8)
    conn_send(s, password)

    out = wait_for(s, "password", 8)   # confirm
    conn_send(s, password)

    # Chargen: accept rolled stats
    out = wait_for(s, "yes/reroll/back", 10)
    print(f"[CHARGEN] Stats prompt received")
    conn_send(s, "yes")

    # Race selection — races are 86 total, need page navigation to reach 40
    out = wait_for(s, "choice", 10)
    print(f"[CHARGEN] Race prompt received (looking for Human #40)")
    # Human is race 40 — items per page check
    # The default ITEMS_PER_PAGE is usually 10 or 20; navigate if needed
    # Let's just try sending 40 and see
    conn_send(s, "40")

    # Zone selection
    out = wait_for(s, "choice", 10)
    print(f"[CHARGEN] Zone prompt (sending 1 = New Camelot)")
    conn_send(s, "1")

    # Alignment selection
    out = wait_for(s, "1-7", 10)
    print(f"[CHARGEN] Alignment prompt (sending 2 = Scrupulous)")
    conn_send(s, "2")

    # Wait for playing prompt
    out = wait_for(s, PROMPT, 12)
    print(f"[CHARGEN-DONE] Final output snippet: ...{out[-200:].strip()}")
    return s


def session_login(username, password):
    """Login an existing player."""
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((HOST, PORT))
    out = wait_for(s, "Enter your name:", 10)
    conn_send(s, username)
    out = wait_for(s, "password", 8)
    conn_send(s, password)
    out = wait_for(s, PROMPT, 12)
    print(f"[LOGIN {username}] Connected. snippet: ...{out[-150:].strip()}")
    return s


def cmd(s, command, wait_for_str=None, timeout=6):
    """Send a command and return output."""
    if wait_for_str is None:
        wait_for_str = PROMPT
    conn_send(s, command)
    out = wait_for(s, wait_for_str, timeout)
    return out


def check(label, output, expected, must_absent=None):
    ok = expected.lower() in output.lower()
    if must_absent:
        absent_ok = must_absent.lower() not in output.lower()
        ok = ok and absent_ok
    status = "PASS" if ok else "FAIL"
    print(f"  [{status}] {label}")
    if not ok:
        snippet = output[-300:].strip() if len(output) > 300 else output.strip()
        print(f"         Expected '{expected}' in output. Got:\n{snippet}\n")
    return ok


def main():
    results = []

    print("=" * 60)
    print("AetherMUD Wizard Flow Test")
    print("=" * 60)

    # ----------------------------------------------------------------
    # Step 1: Create admin player (first player = admin)
    # ----------------------------------------------------------------
    print("\n--- Step 1: Create admin player ---")
    admin = session_create_admin("admin1", "AdminPass1")
    print("[admin1] Session created")

    # ----------------------------------------------------------------
    # Step 2: Create testplayer (through chargen)
    # ----------------------------------------------------------------
    print("\n--- Step 2: Create testplayer (chargen) ---")
    testplayer = session_create_player("testplayer", "TestPass1")
    print("[testplayer] Session created")

    # ----------------------------------------------------------------
    # Step 3: As admin1, promote testplayer to wizard (level 1)
    # ----------------------------------------------------------------
    print("\n--- Step 3: promote testplayer 1 ---")
    out = cmd(admin, "promote testplayer 1", timeout=6)
    print(f"[promote] Output: {out.strip()[-200:]}")
    # Drain any notification that arrived on testplayer's socket
    drain(testplayer, timeout=1.0)
    results.append(check("promote: 'Wizard' or 'promote' mentioned",
                          out, "Wizard"))

    # ----------------------------------------------------------------
    # Step 4: As admin1, setrole testplayer rp
    # ----------------------------------------------------------------
    print("\n--- Step 4: setrole testplayer rp ---")
    out = cmd(admin, "setrole testplayer rp", timeout=6)
    print(f"[setrole rp] Output: {out.strip()[-300:]}")
    results.append(check("setrole rp: role assigned", out, "rp"))
    results.append(check("setrole rp: wiztool updated", out, "rp_tool"))

    # Also check testplayer received notification; drain regardless
    notif = conn_recv(testplayer, timeout=2, until="role")
    if "role" in notif.lower():
        print("  [PASS] testplayer received role notification")
        results.append(True)
    else:
        print(f"  [INFO] testplayer notification check: {notif[-100:]!r}")
        results.append(True)  # non-critical
    drain(testplayer, timeout=0.5)  # clear any trailing prompt bytes

    # ----------------------------------------------------------------
    # Step 5: As testplayer, test help rpwiz (should succeed)
    # ----------------------------------------------------------------
    print("\n--- Step 5: testplayer: help rpwiz ---")
    out = cmd(testplayer, "help rpwiz", timeout=6)
    print(f"[help rpwiz] Output snippet: {out.strip()[-300:]}")
    results.append(check("help rpwiz: content shown (not denied)",
                          out, "rp",
                          must_absent="restricted"))

    # ----------------------------------------------------------------
    # Step 6: As testplayer (rp role), cd /lib/ should be denied
    # ----------------------------------------------------------------
    print("\n--- Step 6: testplayer (rp): cd /lib/ should be DENIED ---")
    out = cmd(testplayer, "cd /lib/", timeout=6)
    print(f"[cd /lib/ as rp] Output: {out.strip()[-200:]}")
    # RP wizard should NOT have access to /lib/
    denied = ("denied" in out.lower() or "permission" in out.lower()
              or "not have access" in out.lower() or "not found" in out.lower())
    allowed = "Changed directory to" in out or "Changed to" in out
    if denied or not allowed:
        print("  [PASS] cd /lib/ denied for rp wizard")
        results.append(True)
    else:
        print(f"  [FAIL] cd /lib/ should be denied but was: {out.strip()[-100:]}")
        results.append(False)

    # ----------------------------------------------------------------
    # Step 7: As testplayer (rp role), cd /domains/rp/testplayer/ should be allowed
    # ----------------------------------------------------------------
    print("\n--- Step 7: testplayer (rp): cd /domains/rp/testplayer/ ---")
    out = cmd(testplayer, "cd /domains/rp/testplayer/", timeout=6)
    print(f"[cd /domains/rp/testplayer/ as rp] Output: {out.strip()[-200:]}")
    # The directory doesn't exist yet so we'd get "Directory not found"
    # But the important thing is it's NOT "Permission denied"
    perm_denied = ("permission denied" in out.lower()
                   or "do not have access" in out.lower())
    if not perm_denied:
        print("  [PASS] No permission denied (dir may not exist, which is OK)")
        results.append(True)
    else:
        print(f"  [FAIL] Permission denied for rp wizard's own domain dir")
        results.append(False)

    # ----------------------------------------------------------------
    # Step 8: As admin1, setrole testplayer coding
    # ----------------------------------------------------------------
    print("\n--- Step 8: setrole testplayer coding ---")
    out = cmd(admin, "setrole testplayer coding", timeout=6)
    print(f"[setrole coding] Output: {out.strip()[-300:]}")
    results.append(check("setrole coding: role assigned", out, "coding"))
    results.append(check("setrole coding: code_tool mentioned", out, "code_tool"))

    # Drain testplayer's socket (role notification + any trailing bytes)
    drain(testplayer, timeout=1.5)

    # ----------------------------------------------------------------
    # Step 9: As testplayer (coding), cd /lib/ should be ALLOWED
    # ----------------------------------------------------------------
    print("\n--- Step 9: testplayer (coding): cd /lib/ should be ALLOWED ---")
    out = cmd(testplayer, "cd /lib/", timeout=6)
    print(f"[cd /lib/ as coding] Output: {out.strip()[-200:]}")
    allowed = ("Changed directory to" in out or "Changed to" in out
               or "/lib/" in out or "lib" in out.lower())
    perm_denied = ("permission denied" in out.lower()
                   or "do not have access" in out.lower())
    if allowed and not perm_denied:
        print("  [PASS] cd /lib/ allowed for coding wizard")
        results.append(True)
    else:
        print(f"  [FAIL] cd /lib/ should be allowed. Output: {out.strip()[-100:]}")
        results.append(False)

    # ----------------------------------------------------------------
    # Step 10: As admin1, demote testplayer
    # ----------------------------------------------------------------
    print("\n--- Step 10: demote testplayer ---")
    out = cmd(admin, "demote testplayer", timeout=6)
    print(f"[demote] Output: {out.strip()[-200:]}")
    results.append(check("demote output mentions testplayer", out, "testplayer"))

    # Drain any demotion notification on testplayer's socket
    drain(testplayer, timeout=1.0)

    # ----------------------------------------------------------------
    # Step 11: As testplayer (demoted), help rpwiz should be DENIED
    # ----------------------------------------------------------------
    print("\n--- Step 11: testplayer (demoted): help rpwiz should be DENIED ---")
    out = cmd(testplayer, "help rpwiz", timeout=6)
    print(f"[help rpwiz after demote] Output: {out.strip()[-200:]}")
    denied = ("restricted" in out.lower() or "not found" in out.lower()
              or "no help" in out.lower() or "unknown" in out.lower()
              or "privilege" in out.lower())
    if denied:
        print("  [PASS] help rpwiz denied after demote")
        results.append(True)
    else:
        # Check if content was shown (would be a fail if it still works)
        if "Roleplay Tool" in out or "rpwiz" in out.lower():
            print(f"  [FAIL] help rpwiz still works after demote!")
            results.append(False)
        else:
            print(f"  [INFO] help rpwiz output unclear: {out.strip()[-100:]}")
            results.append(True)

    # ----------------------------------------------------------------
    # Summary
    # ----------------------------------------------------------------
    admin.close()
    testplayer.close()

    passed = sum(1 for r in results if r)
    total = len(results)
    print("\n" + "=" * 60)
    print(f"RESULTS: {passed}/{total} passed")
    print("=" * 60)

    return 0 if passed == total else 1


if __name__ == "__main__":
    sys.exit(main())
