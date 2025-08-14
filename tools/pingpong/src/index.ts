#!/usr/bin/env node

import { keepPinging } from './keepPinging';
import { PingResult } from './ping';

/**
 * Main entry point for the PingPong application
 */
function main(): void {
  console.log('🏓 PingPong - Starting website pinging...');
  console.log('Target: https://www.yahoo.com');
  console.log('Frequency: 10 pings per second');
  console.log('Press Ctrl+C to stop\n');

  // Keep track of statistics
  let successCount = 0;
  let failureCount = 0;
  let totalResponseTime = 0;

  // Start pinging with custom options
  const stopPinging = keepPinging({
    url: 'https://www.yahoo.com',
    frequency: 10,
    maxPings: 0, // Run indefinitely
    onResult: (result: PingResult, pingCount: number) => {
      if (result.success) {
        successCount++;
      } else {
        failureCount++;
      }
      totalResponseTime += result.responseTime;

      // Print statistics every 50 pings
      if (pingCount % 50 === 0) {
        const avgResponseTime = totalResponseTime / pingCount;
        const successRate = (successCount / pingCount) * 100;
        
        console.log(`\n📊 Statistics after ${pingCount} pings:`);
        console.log(`   Success rate: ${successRate.toFixed(1)}% (${successCount}/${pingCount})`);
        console.log(`   Average response time: ${avgResponseTime.toFixed(1)}ms`);
        console.log(`   Failures: ${failureCount}\n`);
      }
    },
    onError: (error: Error) => {
      console.error('❌ Ping error:', error.message);
    }
  });

  // Handle graceful shutdown
  process.on('SIGINT', () => {
    console.log('\n\n🛑 Received SIGINT. Stopping pings...');
    stopPinging();
    
    const totalPings = successCount + failureCount;
    if (totalPings > 0) {
      const successRate = (successCount / totalPings) * 100;
      const avgResponseTime = totalResponseTime / totalPings;
      
      console.log('\n📈 Final Statistics:');
      console.log(`   Total pings: ${totalPings}`);
      console.log(`   Success rate: ${successRate.toFixed(1)}% (${successCount}/${totalPings})`);
      console.log(`   Average response time: ${avgResponseTime.toFixed(1)}ms`);
      console.log(`   Failures: ${failureCount}`);
    }
    
    console.log('\n👋 Goodbye!');
    process.exit(0);
  });

  process.on('SIGTERM', () => {
    console.log('\n\n🛑 Received SIGTERM. Stopping pings...');
    stopPinging();
    process.exit(0);
  });
}

// Run the main function if this file is executed directly
if (require.main === module) {
  main();
}

export { main };
