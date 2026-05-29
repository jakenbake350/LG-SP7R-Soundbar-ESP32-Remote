# Claude Code Guidelines for This Project

This file helps Claude Code work more effectively on this project.

## Project Overview

ESP32-based IR remote for LG SP7R 7.1 channel soundbar. Two versions available:
- **Simple (6-button)**: Power, Input, Speaker Level, EQ, Menu, Settings
- **Full (15-button)**: All original remote functions

## Key Files

- `src/main.cpp` - 6-button simplified remote (default)
- `src/main_full_15button.cpp` - Complete 15-button remote
- `LG_SP7R_IR_CODES.txt` - All IR codes in Arduino format
- `SP7R.csv` - IR codes for IRDB database (renamed from LG_SP7R_IRDB.csv)
- `README.md` - Main documentation

## Git Workflow Preferences

### Commit Messages
- Keep them SIMPLE and DESCRIPTIVE
- Describe WHAT the files/changes ARE, not detailed changelogs
- Use one-sentence summaries when possible
- Always include Co-Authored-By line

**Good example:**
```
Add Claude Code editor configuration

Editor preferences for development workflow

Co-Authored-By: Claude Sonnet 4.5 <noreply@anthropic.com>
```

**Bad example (too detailed):**
```
Major update: Complete refactor with multiple changes
- Updated file A
- Modified function B
- Changed variable C
- Refactored class D
... (long changelog)
```

### Git Commands
- Use descriptive commit messages, not "Major update"
- For file descriptions in README, focus on what files CONTAIN, not change history
- GitHub username: jakenbake350
- Always use `--force` carefully, confirm first

## Important Notes

### File Naming
- CSV file was renamed: `LG_SP7R_IRDB.csv` → `SP7R.csv`
- Don't reference the old filename

### Hardware Details
- Soundbar model: LG SP7R (NOT SPD7R - that was a typo that got fixed)
- Remote model: AKB76038001
- IR Protocol: NEC, Address: 0x2C (44 decimal)
- All 15 buttons captured and tested

### Battery Power
- TP4056 module has its own USB-C port for charging
- Battery connects to B+/B- on TP4056
- TP4056 OUT+/OUT- goes to ESP32 VIN/GND
- NO cable cutting needed

### Button Layout Philosophy
The 6-button version focuses on soundbar-specific functions NOT available on LG TV remotes, which is why only these buttons were chosen.

## Working with Claude Code (Tips from Boris Cherny)

### 1. Use Plan Mode for Complex Tasks
Start complex, multi-step tasks in plan mode to think through the approach before implementation.

### 2. Invest in CLAUDE.md
Update this file after every correction to avoid repeating mistakes. Claude is good at writing rules for itself.

### 3. Challenge Claude
- Ask Claude to review changes before committing
- Request diffs between branches
- Make Claude prove implementations work

### 4. Use Skills
If you do something more than once a day, consider creating a custom skill for it.

### 5. Be Specific with Prompts
Give clear, detailed instructions. Don't micromanage but do provide context.

## Common Mistakes to Avoid

1. **GitHub Workflow Confusion**: When forking repos, make sure pull requests go to the ORIGINAL repo (probonopd/irdb), not your own fork
2. **Commit Message Style**: Don't use verbose changelogs - simple one-line descriptions are preferred
3. **Model Name**: It's SP7R, not SPD7R
4. **File Descriptions**: Focus on what files ARE, not what changed in them

## Project Status

- ✅ IR codes captured for all 15 buttons
- ✅ 6-button and 15-button remote code working
- ✅ Published to GitHub: https://github.com/jakenbake350/LG-SP7R-Soundbar-ESP32-Remote
- ✅ Submitted to IRDB: Pull request #200
- ⏳ Potential future additions: 3D printed case, complete BOM, assembly guide

## Personal Preferences

- Keep things simple - this isn't a complicated project
- Don't over-engineer solutions
- Focus on what works, not perfect code
- Documentation should be helpful, not exhaustive
