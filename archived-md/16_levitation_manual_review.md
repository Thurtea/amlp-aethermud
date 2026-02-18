**Levitation Manual Review**

Purpose: Capture the unified diff between the two levitation implementations, summarize the differences, and recommend an action for consolidation.

Location:
- lib/psionics/physical/levitation.lpc
- lib/spells/level2/levitation.lpc

Summary:
- The two files are functionally similar (both provide levitation/flying) but follow distinct frameworks: one is implemented as a psionic power (psionic API) and the other as a spell (spell API).
- Key differences: inheritance, naming (power vs spell), cost units (I.S.P. vs P.P.E.), duration formula, components/flags, and the main handler function and properties set on the caster.

Diff (unified):

 --- lib/psionics/physical/levitation.lpc        2026-02-05 13:29:29.575783839 -0400
 +++ lib/spells/level2/levitation.lpc    2026-02-05 13:29:29.579783839 -0400
 @@ -1,38 +1,39 @@
 -// /lib/psionics/physical/levitation.lpc
 -// Physical Psionic - Levitation (varies ISP)
 -// Fly and float using psionic power
 +// /lib/spells/level2/levitation.lpc
 +// Level 2 Spell - Levitation (5 PPE)
 +// Allows caster to float and fly
  
 -inherit "/lib/std/psionic";
 +inherit "/lib/std/spell";
  
  void create() {
      ::create();
      
 -    set_power_name("Levitation");
 -    set_power_id("levitation_psionic");
 -    set_category("physical");
 -    set_power_level(1);
 +    set_spell_name("Levitation");
 +    set_spell_id("levitation");
 +    set_spell_level(2);
 +    set_spell_type("movement");
 +    set_casting_time(1);
      
 -    set_short("a levitation psionic power");
 +    set_short("a levitation spell");
      set_long(
 -        "Levitation allows the psychic to fly using mental
 + power at a speed "
 -        "of 10 mph per I.S.P. spent. Can hover motionless 
 +or fly at speed. "
 -        "Each I.S.P. provides 10 minutes of flight at that
 + speed. Costs "
 -        "vary: 8 I.S.P. for 10 mph, 16 for 20 mph, etc. Ra
 +nge: Self."
 +        "Levitation allows the caster to rise into the air
 + and float at will. "
 +        "Maximum height is 100 feet. Movement speed is app
 +roximately half normal "
 +        "running speed. The spell lasts 5 minutes per leve
 +l. "
 +        "Costs 5 P.P.E. to cast."
      );
      
 -    set_isp_cost(8);  // Base cost
 +    set_ppe_cost(5);
      set_range("Self");
 -    set_duration("10 minutes per I.S.P.");
 +    set_duration("5 minutes per level");
      set_saving_throw("None");
      set_damage("None");
      
 -    set_mental_endurance_required(0);
 -    set_requires_concentration(0);  // Can maintain while 
 +doing other things
 +    set_components(({}));
 +    set_verbal(1);
 +    set_somatic(1);
  }
  
 -int manifest_power(object caster, mixed target, string arg
 +s) {
 -    int speed = 10;  // mph
 -    int cost, duration;
 +int cast_spell(object caster, mixed target, string args) {
 +    int duration;
 +    
 +    if (!caster) return 0;
 +    
 @@ -41,35 +42,16 @@
 +        return 0;
 +    }
 +    
 -    // Parse speed from args if provided
 -    if (args && sscanf(args, "%d", speed) == 1) {
 -        if (speed < 10) speed = 10;
 -        if (speed > 100) speed = 100;  // Max 100 mph
 -        
 -        // Must be multiple of 10
 -        speed = (speed / 10) * 10;
 -    }
 -    
 -    cost = (speed / 10) * 8;
 -    duration = 600;  // 10 minutes base
 -    
 -    // Check if caster has enough ISP (simplified - would 
 +    duration = caster->query_spell_caster_level() * 300;  
 +// 5 min/level in seconds
 -    // check actual ISP in real system)
 -    if (cost > 8) {
 -        tell_object(caster, "Levitating at " + speed + " m
 +    tell_object(caster, "You rise gracefully into the air!");
 +    tell_room(environment(caster),
 +        caster->query_cap_name() + " rises gracefully into
 + the air!",
 +        ({caster}));
 +    
 +    caster->set_property("levitating", 1);
 - (8 I.S.P.)");
 -        speed = 10;
 -        cost = 8;
 -    }
 -    
 -    duration = 600;  // 10 minutes base
 -    
 -    // Check if caster has enough ISP (simplified - would 
 -    // check actual ISP in real system)
 -    if (cost > 8) {
 -        tell_object(caster, "Levitating at " + speed + " m
 -ph costs " + cost + " I.S.P.");
 -        tell_object(caster, "Using default speed of 10 mph
 - (8 I.S.P.)");
 -        speed = 10;
 -        cost = 8;
 -    }
 -    
 -    tell_object(caster, "You lift into the air using psion
 -ic power!");
 -    tell_room(environment(caster),
 -        caster->query_cap_name() + " rises into the air!",
 -        ({caster}));
 -    
 -    caster->set_property("levitating", 1);
 -    caster->set_property("flying", 1);
 -    caster->set_property("flight_speed", speed);
 -    caster->set_property("altitude", 10);
 -    
 -    call_out("end_levitation", duration, caster);
 -    
 -    return 1;
 +    caster->set_property("flying", 1);  // Allows passage 
 +through certain barriers
 +    caster->set_property("altitude", 10);  // 10 feet defa
 +ult height
 +    
 +    call_out("end_levitation", duration, caster);
 +    
 +    return 1;
 +@@ -81,11 +63,10 @@
 +    caster->remove_property("levitating");
 +    caster->remove_property("flying");
 -    caster->remove_property("flight_speed");
 +    caster->remove_property("altitude");
 +    
 +    tell_object(caster, "Your levitation spell ends and yo
 +u drift gently to the ground.");
 +    tell_room(environment(caster),
 +        caster->query_cap_name() + " drifts gently to the 
 +ground.",
 +        ({caster}));
 +}
 +
 +
 +Analysis:
 +- The psionic file uses ISP-based costs and allows configurable speed; it sets a flight_speed property and different messaging.
 +- The spell file uses PPE cost, a level-based duration, and sets verbal/somatic flags. It removes flight_speed handling and simplifies motion to a default altitude.
 +- Because the two systems are different (psionic vs spell frameworks), keeping both copies may be necessary iff both subsystems are actively used by the mudlib. If only one system is in use, prefer the implementation matching that subsystem.
 +
 +Recommendation:
 +- If the project uses the spell framework (lib/std/spell) for movement effects, keep lib/spells/level2/levitation.lpc and deprecate the psionic version.
 +- If both psionics and spells must be supported, refactor to a shared implementation: extract core levitation behavior into lib/skills/levitation_core.c (or similar), then implement thin adapters in lib/spells/level2/levitation.lpc and lib/psionics/physical/levitation.lpc that translate spell/psionic parameters into shared API calls.
 +- Do NOT delete either file without:
 +  1) Grepping the codebase for references to both paths and runtime lookups.
 +  2) Running a quick smoke test after any removal or refactor: rebuild and start the driver; exercise both spell and psionic casting paths.
 +
 +Suggested commands:
 +- Show unified diff (already captured): diff -u lib/psionics/physical/levitation.lpc lib/spells/level2/levitation.lpc
 +- Find references: egrep -R --include='*.lpc' --include='*.c' --include='*.h' "levitation.lpc" lib/ src/ Makefile
 +- Backup before changing: tar -czf /tmp/levitation-backup-$(date +%F_%H%M%S).tar.gz lib/psionics/physical/levitation.lpc lib/spells/level2/levitation.lpc
 +- If consolidating to spells-first approach: replace psionic file with a thin wrapper that calls the spell API or shared core.
 +
 +Decision template (example git steps):
 +1. Create branch: git checkout -b consolidate/levitation
 +2. Run tests/build: ./mud.sh rebuild
 +3. Implement shared core and adapter files.
 +4. Update any references and run smoke tests: ./mud.ctl start; cast levitation as spell and psionic user.
 +5. Commit and open PR for review.
 +
 +Conclusion: The two files are not byte-for-byte identical and map to two different subsystems. I recommend refactoring to a shared core and adapters; if that's not feasible in the short term, choose the subsystem you maintain (likely spells) and convert the other to a wrapper that forwards to the canonical implementation.
