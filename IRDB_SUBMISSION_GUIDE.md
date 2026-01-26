# LG SP7R Soundbar - IR Code Database Submission Guide

## Codes Successfully Captured
All 15 buttons from LG SP7R soundbar remote (Model: AKB76038001) have been captured using NEC protocol.

## How to Submit to IRDB (probonopd/irdb)

### Step 1: Fork the Repository
1. Go to https://github.com/probonopd/irdb
2. Click the "Fork" button in the top right
3. Wait for your fork to be created

### Step 2: Add Your CSV File
1. Navigate to `codes/LG/Soundbar/` in your fork (create folders if needed)
2. Upload `LG_SP7R_IRDB.csv`
3. Commit with message: "Add LG SP7R soundbar IR codes (Model: AKB76038001)"

### Step 3: Create Pull Request
1. Go to the Pull Requests tab
2. Click "New Pull Request"
3. Title: "Add LG SP7R soundbar remote codes"
4. Description:
   ```
   Adding IR codes for LG SP7R 7.1 channel soundbar
   Remote Model: AKB76038001
   Protocol: NEC
   Address: 0x2C (44 decimal)

   All 15 buttons captured and tested working.
   Includes: Power, Mute, Input switching, Volume controls, EQ, Bluetooth,
   navigation buttons, and settings menu controls.
   ```

### Step 4: Submit
Click "Create Pull Request"

---

## Alternative: Create GitHub Gist

If you prefer a simpler sharing method:

1. Go to https://gist.github.com
2. Create a new gist with filename: `LG_SP7R_IR_Codes.txt`
3. Paste the contents of `LG_SP7R_IR_CODES.txt`
4. Make it public
5. Share the link in IR remote communities

---

## Files Ready for Submission

- **LG_SP7R_IRDB.csv** - Ready for IRDB database
- **LG_SP7R_IR_CODES.txt** - Complete documentation with multiple formats
- **LIRC_FORMAT.conf** - LIRC configuration file (see below)

---

## Communities to Share With

- r/hometheater on Reddit
- r/BudgetAudiophile on Reddit
- IRDB GitHub discussions
- Home automation forums
