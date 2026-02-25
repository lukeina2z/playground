const { runOnceTest, simulateTraffic } = require("./src/app");
// const {recordRequestMetric }= require("./src/metric");

async function runForever() {
  let keepRunning = true;
  while (keepRunning) {
    // recordRequestMetric();
    await simulateTraffic();
    // const cooldown = Math.floor(Math.random() * 10000) + 5000; // 5-15 seconds
    const cooldown = Math.floor(Math.random() * 120000) + 60000; // 1-3 minutes
    await sleep(cooldown);
    // keepRunning = false;
  }
}

function sleep(ms) {
  return new Promise(resolve => setTimeout(resolve, ms));
}

runForever();

// runOnceTest();
