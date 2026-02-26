Integration smoke test — how to run

1. On the running MUD driver (as a wizard or via the driver console), load and run the test object:

   object it = load_object("/lib/test/integration_smoke_test");
   it->run_all();

2. After running, view results on the MUD host:

   cat /tmp/integration_smoke_test.txt

Notes:
- This test attempts to load the chargen daemon and exercise stat rolling and basic race/OCC loading.
- It is a non-interactive static test and will not perform full in-game character creation or combat flows.
- Use this to detect missing loads and major early failures before manual in-game QA.
