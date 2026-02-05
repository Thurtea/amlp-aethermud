# Spell Levels 4-15

This directory structure organizes spells by their level (1-15).

## Current Status

### Level 1 Spells (10 PPE cost)
- armor_of_ithan.lpc

### Level 2 Spells (10-20 PPE cost)
- swim_as_a_fish.lpc

### Level 3 Spells (15-30 PPE cost)
- fireball.lpc
- read_aura.lpc

### Level 4 Spells
- (Pending implementation)

### Level 5 Spells
- heal_wounds.lpc

### Level 6 Spells
- tongues.lpc
- lightning_bolt.lpc
- magic_shield.lpc

### Levels 7-15
- (Pending implementation)

## Adding New Spells

When adding a spell:
1. Place it in the appropriate level directory
2. Inherit from /lib/std/spell.lpc
3. Set proper PPE cost, level, and effects
4. Update this README

## Rifts Spell Level Reference

Levels 1-3: Basic utility and combat spells (10-30 PPE)
Levels 4-6: Intermediate spells (30-60 PPE)
Levels 7-9: Advanced spells (60-120 PPE)
Levels 10-12: Master-level spells (120-200 PPE)
Levels 13-15: Grand master spells (200+ PPE)
