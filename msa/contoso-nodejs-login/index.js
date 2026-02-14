const testingApp = require("./src/app");
// const {recordRequestMetric }= require("./src/metric");

async function runForever() {
  let keepRunning = true;
  while (keepRunning) {
    // recordRequestMetric();
    await testingApp();
    await sleep(60000);  // Wait for 1 second
    // keepRunning = false;
  }
}

function sleep(ms) {
  return new Promise(resolve => setTimeout(resolve, ms));
}

runForever();
