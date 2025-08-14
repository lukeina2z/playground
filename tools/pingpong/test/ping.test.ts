import axios from 'axios';
import { pingWeb, PingResult } from '../src/ping';

// Mock axios
jest.mock('axios');
const mockedAxios = axios as jest.Mocked<typeof axios>;

describe('pingWeb', () => {
  beforeEach(() => {
    jest.clearAllMocks();
    jest.clearAllTimers();
    jest.useFakeTimers();
  });

  afterEach(() => {
    jest.useRealTimers();
  });

  it('should return success result for successful HTTP request', async () => {
    // Arrange
    const mockResponse = {
      status: 200,
      statusText: 'OK',
      data: 'Hello World',
      headers: {},
      config: { url: 'https://example.com' },
    };
    mockedAxios.get.mockResolvedValue(mockResponse);

    // Act
    const promise = pingWeb('https://example.com');
    jest.advanceTimersByTime(100); // Simulate 100ms response time
    const result = await promise;

    // Assert
    expect(result.success).toBe(true);
    expect(result.statusCode).toBe(200);
    expect(result.responseTime).toBeGreaterThanOrEqual(0);
    expect(result.contentLength).toBe(11); // 'Hello World'.length
    expect(result.timestamp).toBeInstanceOf(Date);
    expect(result.error).toBeUndefined();
  });

  it('should return failure result for HTTP error status', async () => {
    // Arrange
    const mockResponse = {
      status: 404,
      statusText: 'Not Found',
      data: 'Not Found',
      headers: {},
      config: { url: 'https://example.com/notfound' },
    };
    mockedAxios.get.mockResolvedValue(mockResponse);

    // Act
    const result = await pingWeb('https://example.com/notfound');

    // Assert
    expect(result.success).toBe(false);
    expect(result.statusCode).toBe(404);
    expect(result.responseTime).toBeGreaterThanOrEqual(0);
    expect(result.contentLength).toBe(9); // 'Not Found'.length
    expect(result.timestamp).toBeInstanceOf(Date);
    expect(result.error).toBeUndefined();
  });

  it('should return error result for network error', async () => {
    // Arrange
    const networkError = new Error('Network Error');
    mockedAxios.get.mockRejectedValue(networkError);

    // Act
    const result = await pingWeb('https://invalid-url.com');

    // Assert
    expect(result.success).toBe(false);
    expect(result.statusCode).toBeUndefined();
    expect(result.responseTime).toBeGreaterThanOrEqual(0);
    expect(result.contentLength).toBeUndefined();
    expect(result.timestamp).toBeInstanceOf(Date);
    expect(result.error).toBe('Network Error');
  });

  it('should use default URL when none provided', async () => {
    // Arrange
    const mockResponse = {
      status: 200,
      statusText: 'OK',
      data: 'Yahoo content',
      headers: {},
      config: { url: 'https://www.yahoo.com' },
    };
    mockedAxios.get.mockResolvedValue(mockResponse);

    // Act
    await pingWeb();

    // Assert
    expect(mockedAxios.get).toHaveBeenCalledWith(
      'https://www.yahoo.com',
      expect.objectContaining({
        timeout: 5000,
        validateStatus: expect.any(Function),
        headers: {
          'User-Agent': 'PingPong/1.0.0'
        }
      })
    );
  });

  it('should use custom timeout when provided', async () => {
    // Arrange
    const mockResponse = {
      status: 200,
      statusText: 'OK',
      data: 'content',
      headers: {},
      config: { url: 'https://example.com' },
    };
    mockedAxios.get.mockResolvedValue(mockResponse);

    // Act
    await pingWeb('https://example.com', 10000);

    // Assert
    expect(mockedAxios.get).toHaveBeenCalledWith(
      'https://example.com',
      expect.objectContaining({
        timeout: 10000
      })
    );
  });

  it('should handle non-Error exceptions', async () => {
    // Arrange
    mockedAxios.get.mockRejectedValue('String error');

    // Act
    const result = await pingWeb('https://example.com');

    // Assert
    expect(result.success).toBe(false);
    expect(result.error).toBe('Unknown error');
  });
});
