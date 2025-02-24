var console_api = require('./');

console_api.setPalette(console_api.palettes.desaturated);

console.log('Changing title...');
console_api.setTitle('Test');
setTimeout(function () {
  console.log('Exiting...');
}, 2000);
