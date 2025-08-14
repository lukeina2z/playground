import { keepPinging } from '../src/keepPinging';
import { pingWeb } from '../src/ping';

// Mock the pingWeb function
jest.mock('../src/ping');
const mockedPingWeb = pingWeb as jest.MockedFunction<typeof pingWeb>;

// Mock console methods
const consoleSpy = {
  log: jest.spyOn(console, 'log').mockImplementation(),
  error: jest.spyOn(console, 'error').mockImplementation(),
};

describe('keepPinging', () => {
  beforeEach(() => {
    jest.clearAllMocks();
    jest.clearAllTimers();
    jest.useFakeTimers();
    consoleSpy.log.mockClear();
    consoleSpy.error.mockClear();
  });

  afterEach(() => {
    jest.useRealTimers();
  });

  afterAll(() => {
    consoleSpy.log.mockRestore();
    consoleSpy.error.mockRestore();
  });

  it('should ping at the specified frequency', async () => {
    // Arrange
    const mockResult = {
      success: true,
      statusCode: 200,
      responseTime: 100,
      contentLength: 1000,
      timestamp: new Date(),
    };
    mockedPingWeb.mockResolvedValue(mockResult);

    // Act
    const stopPinging = keepPinging({ frequency: 2 }); // 2 pings per second

    // Advance time to trigger multiple pings
    await jest.advanceTimersByTimeAsync(0); // Initial ping
    await jest.advanceTimersByTimeAsync(500); // Second ping (after 500ms)
    await jest.advanceTimersByTimeAsync(500); // Third ping (after another 500ms)

    stopPinging();

    // Assert
    expect(mockedPingWeb).toHaveBeenCalledTimes(3);
  });

  it('should call onResult callback with ping results', async () => {
    // Arrange
    const mockResult = {
      success: true,
      statusCode: 200,
      responseTime: 150,
      contentLength: 500,
      timestamp: new Date(),
    };
    mockedPingWeb.mockResolvedValue(mockResult);
    const onResultCallback = jest.fn();

    // Act
    const stopPinging = keepPinging({
      frequency: 10,
      onResult: onResultCallback,
    });

    await jest.advanceTimersByTimeAsync(0); // Initial ping
    await jest.advanceTimersByTimeAsync(100); // Second ping

    stopPinging();

    // Assert
    expect(onResultCallback).toHaveBeenCalledTimes(2);
    expect(onResultCallback).toHaveBeenNthCalledWith(1, mockResult, 1);
    expect(onResultCallback).toHaveBeenNthCalledWith(2, mockResult, 2);
  });

  it('should stop after maxPings is reached', async () => {
    // Arrange
    const mockResult = {
      success: true,
      statusCode: 200,
      responseTime: 100,
      timestamp: new Date(),
    };
    mockedPingWeb.mockResolvedValue(mockResult);

    // Act
    keepPinging({
      frequency: 10,
      maxPings: 2,
    });

    await jest.advanceTimersByTimeAsync(0); // First ping
    await jest.advanceTimersByTimeAsync(100); // Second ping
    await jest.advanceTimersByTimeAsync(100); // Should not trigger third ping

    // Assert
    expect(mockedPingWeb).toHaveBeenCalledTimes(2);
    expect(consoleSpy.log).toHaveBeenCalledWith('Completed 2 pings. Stopping.');
  });

  it('should handle ping errors gracefully', async () => {
    // Arrange
    const error = new Error('Network timeout');
    mockedPingWeb.mockRejectedValue(error);
    const onErrorCallback = jest.fn();

    // Act
    const stopPinging = keepPinging({
      frequency: 1,
      onError: onErrorCallback,
    });

    await jest.advanceTimersByTimeAsync(0); // Initial ping that will fail

    stopPinging();

    // Assert
    expect(onErrorCallback).toHaveBeenCalledWith(error);
    expect(consoleSpy.error).toHaveBeenCalledWith('Ping #1 error:', 'Network timeout');
  });

  it('should use default options when none provided', async () => {
    // Arrange
    const mockResult = {
      success: true,
      statusCode: 200,
      responseTime: 100,
      timestamp: new Date(),
    };
    mockedPingWeb.mockResolvedValue(mockResult);

    // Act
    const stopPinging = keepPinging();

    await jest.advanceTimersByTimeAsync(0); // Initial ping

    stopPinging();

    // Assert
    expect(mockedPingWeb).toHaveBeenCalledWith('https://www.yahoo.com');
  });

  it('should use custom URL when provided', async () => {
    // Arrange
    const mockResult = {
      success: true,
      statusCode: 200,
      responseTime: 100,
      timestamp: new Date(),
    };
    mockedPingWeb.mockResolvedValue(mockResult);

    // Act
    const stopPinging = keepPinging({
      url: 'https://custom-url.com',
    });

    await jest.advanceTimersByTimeAsync(0); // Initial ping

    stopPinging();

    // Assert
    expect(mockedPingWeb).toHaveBeenCalledWith('https://custom-url.com');
  });

  it('should log ping results to console', async () => {
    // Arrange
    const mockResult = {
      success: true,
      statusCode: 200,
      responseTime: 123,
      timestamp: new Date(),
    };
    mockedPingWeb.mockResolvedValue(mockResult);

    // Act
    const stopPinging = keepPinging();

    await jest.advanceTimersByTimeAsync(0); // Initial ping

    stopPinging();

    // Assert
    expect(consoleSpy.log).toHaveBeenCalledWith(
      'Ping #1: SUCCESS - 123ms - Status: 200'
    );
  });

  it('should return a stop function that clears the interval', async () => {
    // Arrange
    const mockResult = {
      success: true,
      statusCode: 200,
      responseTime: 100,
      timestamp: new Date(),
    };
    mockedPingWeb.mockResolvedValue(mockResult);

    // Act
    const stopPinging = keepPinging({ frequency: 10 });

    await jest.advanceTimersByTimeAsync(0); // Initial ping
    await jest.advanceTimersByTimeAsync(100); // Second ping

    expect(mockedPingWeb).toHaveBeenCalledTimes(2);

    stopPinging();

    await jest.advanceTimersByTimeAsync(100); // Should not trigger another ping

    // Assert
    expect(mockedPingWeb).toHaveBeenCalledTimes(2); // Still only 2 calls
    expect(consoleSpy.log).toHaveBeenCalledWith('Stopped pinging after 2 attempts.');
  });
});
