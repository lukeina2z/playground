import { pingWeb, PingResult } from './ping';

/**
 * Interface for keep pinging options
 */
export interface KeepPingingOptions {
  url?: string;
  frequency?: number; // pings per second
  maxPings?: number; // maximum number of pings (0 = unlimited)
  onResult?: (result: PingResult, pingCount: number) => void;
  onError?: (error: Error) => void;
}

/**
 * Keeps pinging a website at a specified frequency
 * @param options - Configuration options for keep pinging
 * @returns A function to stop the pinging
 */
export function keepPinging(options: KeepPingingOptions = {}): () => void {
  const {
    url = 'https://www.yahoo.com',
    frequency = 10, // 10 times per second
    maxPings = 0, // unlimited by default
    onResult,
    onError
  } = options;

  const interval = 1000 / frequency; // Convert frequency to milliseconds
  let pingCount = 0;
  // eslint-disable-next-line prefer-const
  let intervalId: NodeJS.Timeout | undefined;

  const ping = async (): Promise<void> => {
    try {
      pingCount++;
      const result = await pingWeb(url);
      
      // Log the result
      console.log(`Ping #${pingCount}: ${result.success ? 'SUCCESS' : 'FAILED'} - ${result.responseTime}ms - Status: ${result.statusCode || 'N/A'}`);
      
      // Call the callback if provided
      if (onResult) {
        onResult(result, pingCount);
      }

      // Stop if we've reached the maximum number of pings
      if (maxPings > 0 && pingCount >= maxPings) {
        if (intervalId) {
          clearInterval(intervalId);
        }
        console.log(`Completed ${pingCount} pings. Stopping.`);
      }
    } catch (error) {
      const err = error instanceof Error ? error : new Error('Unknown error during ping');
      console.error(`Ping #${pingCount} error:`, err.message);
      
      if (onError) {
        onError(err);
      }
    }
  };

  // Start pinging immediately and then at intervals
  ping();
  intervalId = setInterval(ping, interval);

  // Return a function to stop the pinging
  return (): void => {
    if (intervalId) {
      clearInterval(intervalId);
    }
    console.log(`Stopped pinging after ${pingCount} attempts.`);
  };
}
