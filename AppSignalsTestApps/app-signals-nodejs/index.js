const testingApp = require("./src/app");
const {recordRequestMetric }= require("./src/metric");

// const awsCalls = require('./src/awsS3Test');

async function runForever() {
  while (true) {
    recordRequestMetric();
    await testingApp();
    // await awsCalls.s3Call();
    await sleep(10000);  // Wait for 1 second
  }
}

function sleep(ms) {
  return new Promise(resolve => setTimeout(resolve, ms));
}

// Start the loop
runForever();
