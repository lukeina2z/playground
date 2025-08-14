import axios from 'axios';

export async function pingWeb(url: string): Promise<string> {
  try {
    const response = await axios.get(url, { timeout: 5000 });
    const dataLength = typeof response.data === 'string' ? response.data.length : JSON.stringify(response.data).length;
    return `Status: ${response.status}, Length: ${dataLength}`;
  } catch (error) {
    return `Error: ${error instanceof Error ? error.message : 'Unknown error'}`;
  }
}

export function keepPinging(urlFoo: string = 'https://www.yahoo.com', urlBar: string = ''): void {
  const interval = setInterval(async () => {
    const result = await pingWeb(urlFoo);


    if (urlBar) {
      const result2 = await pingWeb(urlBar);
      console.log(`${new Date().toISOString()}: ${result2}`);
    }
    
    console.log(`${new Date().toISOString()}: ${result}`);
  }, 100); // 10 times per second (1000ms / 10 = 100ms)

  // Graceful shutdown
  process.on('SIGINT', () => {
    clearInterval(interval);
    console.log('\nPinging stopped.');
    process.exit(0);
  });
}