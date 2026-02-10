const testingApp = require("./src/app");
const {recordRequestMetric }= require("./src/metric");

// const awsCalls = require('./src/awsS3Test');

async function runForever() {
  let keepRunning = true;
  while (keepRunning) {
    recordRequestMetric();
    await testingApp();
    // await awsCalls.s3Call();
    // await sleep(10000);  // Wait for 1 second
    keepRunning = false;
  }
}

function sleep(ms) {
  return new Promise(resolve => setTimeout(resolve, ms));
}

// Start the loop
runForever();
