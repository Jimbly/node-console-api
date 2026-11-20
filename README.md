Native Node.js bindings for the Win32 Console API
============================

Usage:
```javascript
const console_api = require('console-api');

console_api.allocConsole(); // If you're running in a Win32 App (e.g. Electron) and don't yet have a console
console_api.setPalette(console_api.palettes.solarized_dark);
console_api.setTitle('New Title!');
```

Palettes are an array of 16 RGB values in the form [0xRRGGBB, 0xRRGGBB, ...]

Note: though this module can be included on any platform, it currently does nothing except on Win32.