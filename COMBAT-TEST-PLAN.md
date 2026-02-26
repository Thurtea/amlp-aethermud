# Combat Test Plan

## Test Cases

- [ ] **1. Player equips vibro-sword, attacks goblin**
  - *Expected outcome:* Goblin takes correct vibro-sword damage (2d6 MD if using vibro-sword template).

- [ ] **2. Player equips combat armor, gets hit**
  - *Expected outcome:* Armor absorbs damage up to its durability; player HP/SDC is not reduced until armor is depleted.

- [ ] **3. Player with 60% wp_sword → verify +3 strike bonus applies**
  - *Expected outcome:* Player receives +3 strike bonus (60/20 = 3) on attack rolls with swords.

- [ ] **4. MDC creature vs SDC weapon → verify 1/100 damage scaling**
  - *Expected outcome:* SDC weapon deals only 1/100th damage to MDC creature (minimum 1 point).

- [ ] **5. Armor durability reaches 0 → verify "armor destroyed" message**
  - *Expected outcome:* When armor durability is reduced to 0, player receives "armor is destroyed!" message and further damage is not absorbed by armor.
