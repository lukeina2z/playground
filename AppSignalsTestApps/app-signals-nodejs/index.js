const testingApp = require("./src/app");

async function runForever() {
  while (true) {
    await testingApp();
    await sleep(10000);  // Wait for 1 second
  }
}

function sleep(ms) {
  return new Promise(resolve => setTimeout(resolve, ms));
}

// Start the loop
runForever();
