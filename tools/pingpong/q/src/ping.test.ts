import { pingWeb } from './ping';
import axios from 'axios';

jest.mock('axios');
const mockedAxios = axios as jest.Mocked<typeof axios>;

describe('pingWeb', () => {
  beforeEach(() => {
    jest.clearAllMocks();
  });

  it('should return success message when request succeeds', async () => {
    const mockResponse = {
      status: 200,
      data: '<html>test content</html>'
    };
    mockedAxios.get.mockResolvedValue(mockResponse);

    const result = await pingWeb('https://example.com');
    
    expect(result).toBe('Status: 200, Length: 26');
    expect(mockedAxios.get).toHaveBeenCalledWith('https://example.com', { timeout: 5000 });
  });

  it('should return error message when request fails', async () => {
    const mockError = new Error('Network Error');
    mockedAxios.get.mockRejectedValue(mockError);

    const result = await pingWeb('https://invalid-url.com');
    
    expect(result).toBe('Error: Network Error');
  });

  it('should handle unknown errors', async () => {
    mockedAxios.get.mockRejectedValue('Unknown error');

    const result = await pingWeb('https://example.com');
    
    expect(result).toBe('Error: Unknown error');
  });
});