import axios from 'axios';

/**
 * Interface for ping result
 */
export interface PingResult {
  success: boolean;
  statusCode?: number;
  responseTime: number;
  contentLength?: number;
  error?: string;
  timestamp: Date;
}

/**
 * Pings a website and returns information about the response
 * @param url - The URL to ping (defaults to https://www.yahoo.com)
 * @param timeout - Request timeout in milliseconds (defaults to 5000)
 * @returns Promise<PingResult> - Result of the ping operation
 */
export async function pingWeb(url: string = 'https://www.yahoo.com', timeout: number = 5000): Promise<PingResult> {
  const startTime = Date.now();
  const timestamp = new Date();

  try {
    const response = await axios.get(url, {
      timeout,
      validateStatus: () => true, // Accept any status code
      headers: {
        'User-Agent': 'PingPong/1.0.0'
      }
    });

    const responseTime = Date.now() - startTime;

    return {
      success: response.status >= 200 && response.status < 400,
      statusCode: response.status,
      responseTime,
      contentLength: typeof response.data === 'string' ? response.data.length : JSON.stringify(response.data || '').length,
      timestamp
    };
  } catch (error) {
    const responseTime = Date.now() - startTime;
    
    return {
      success: false,
      responseTime,
      error: error instanceof Error ? error.message : 'Unknown error',
      timestamp
    };
  }
}
