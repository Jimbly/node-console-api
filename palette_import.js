const assert = require('assert');
const fs = require('fs');

function matchAll(str, re) {
  let ret = [];
  let m;
  do {
    m = re.exec(str);
    if (m) {
      ret.push(m[1]);
    }
  } while (m);
  return ret;
}

let base = 'F:/src/MicrosoftTerminal/src/tools/ColorTool/schemes';
let dir = fs.readdirSync(base);
dir = dir.filter((s) => s.endsWith('.itermcolors'));
for (let ii = 0; ii < dir.length; ++ii) {
	let fn = base + '/' + dir[ii];
	let data = fs.readFileSync(fn, 'utf8');
	let dicts = matchAll(data, /(<key>[^/]+<\/key>\s+<dict>(?:[^/]*\/){6,10}[^/]+<\/dict>)/g);
	dicts = dicts.map((text) => {
		let key = text.match(/<key>([^/]+)<\/key>/)[1];
		let values = matchAll(text, /<real>([0-9.]+)<\/real>/g);
		assert.equal(values.length, 3);
		values = values.map((a) => ('0' + ((Number(a) * 255) | 0).toString(16)).slice(-2)).join('');
		return { key, values };
	});
	let d2 = {};
	for (let jj = 0; jj < dicts.length; ++jj) {
		d2[dicts[jj].key] = dicts[jj].values;
	}
	let ret = [];
	for (let jj = 0; jj < 16; ++jj) {
		let key = `Ansi ${jj} Color`;
		assert(d2[key]);
		ret.push(`0x${d2[key]}`);
	}
	console.log(`${dir[ii].slice(0, -12)}: [${ret.join(', ')}],`);
}