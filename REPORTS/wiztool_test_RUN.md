Wiztool smoke test — how to run

1. On the running MUD driver (as a wizard or via the driver console), load and run the test object:

   object ob = load_object("/lib/test/wiztool_smoke_test");
   ob->run_tests();

2. After running, view results on the MUD host:

   cat /tmp/wiztool_smoke_test.txt

Notes:
- The test verifies that each wiz-tool object loads and that expected handler functions exist (e.g. `cmd_code`, `cmd_rp`, `do_call`).
- This is a static/smoke test only — it does not simulate an interactive `this_player()` environment, nor does it exercise gameplay flows (character creation, combat, spells, etc.).
- Use this test to quickly detect load errors or missing handlers before in-game manual testing.
