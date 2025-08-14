# PingPong 🏓

A TypeScript Node.js project that continuously pings websites to monitor their availability and response times.

## Features

- **pingWeb**: Function to ping a website and get detailed response information
- **keepPinging**: Function to continuously ping a website at a specified frequency (default: 10 times per second)
- **Real-time statistics**: Track success rates, response times, and failure counts
- **Graceful shutdown**: Handle SIGINT/SIGTERM signals properly
- **Comprehensive testing**: Full unit test coverage with Jest
- **TypeScript**: Fully typed with strict TypeScript configuration
- **Linting**: ESLint configuration with TypeScript support
- **Auto-rebuild**: Watch modes for automatic TypeScript compilation and app restart

## Installation

```bash
npm install
```

## Usage

### Development Mode
```bash
npm run dev              # Run once with ts-node
npm run dev:watch        # Run with auto-restart on file changes
```

### Production Mode
```bash
npm run build            # Build once
npm start               # Run compiled version once

# Watch modes for production
npm run build:watch     # Auto-rebuild TypeScript on changes
npm run start:watch     # Auto-restart compiled app on changes
npm run watch           # Both build:watch and start:watch together
```

### Running Tests
```bash
# Run tests once
npm test

# Run tests in watch mode
npm run test:watch
```

### Linting
```bash
# Check for linting issues
npm run lint

# Fix linting issues automatically
npm run lint:fix
```

## Watch Modes

The project includes several watch modes for automatic rebuilding and restarting:

### 1. Development Watch (`npm run dev:watch`)
- **Best for**: Active development and debugging
- **What it does**: Watches `src/` files and restarts the TypeScript application directly using ts-node
- **Pros**: Fast startup, no compilation step needed
- **Cons**: Slightly slower execution than compiled JavaScript

### 2. Build Watch (`npm run build:watch`)
- **Best for**: Monitoring compilation errors
- **What it does**: Watches `src/` files and automatically recompiles TypeScript to `dist/`
- **Use case**: Run this in one terminal while developing

### 3. Start Watch (`npm run start:watch`)
- **Best for**: Testing the compiled application
- **What it does**: Watches `dist/` files and restarts the compiled Node.js application
- **Use case**: Run this in another terminal alongside `build:watch`

### 4. Full Watch (`npm run watch`)
- **Best for**: Production-like development workflow
- **What it does**: Runs both `build:watch` and `start:watch` concurrently
- **Pros**: Tests the actual compiled output, closest to production
- **Cons**: Slightly slower due to compilation step

### Recommended Workflows

**For rapid development:**
```bash
npm run dev:watch
```

**For production-like testing:**
```bash
npm run watch
```

**For manual control:**
```bash
# Terminal 1
npm run build:watch

# Terminal 2
npm run start:watch
```

## API

### pingWeb(url?, timeout?)

Pings a website and returns detailed information about the response.

**Parameters:**
- `url` (string, optional): The URL to ping. Defaults to 'https://www.yahoo.com'
- `timeout` (number, optional): Request timeout in milliseconds. Defaults to 5000

**Returns:** `Promise<PingResult>`

```typescript
interface PingResult {
  success: boolean;
  statusCode?: number;
  responseTime: number;
  contentLength?: number;
  error?: string;
  timestamp: Date;
}
```

**Example:**
```typescript
import { pingWeb } from './src/ping';

const result = await pingWeb('https://www.google.com');
console.log(result);
```

### keepPinging(options?)

Continuously pings a website at a specified frequency.

**Parameters:**
- `options` (KeepPingingOptions, optional): Configuration options

```typescript
interface KeepPingingOptions {
  url?: string;           // URL to ping (default: 'https://www.yahoo.com')
  frequency?: number;     // Pings per second (default: 10)
  maxPings?: number;      // Maximum number of pings (default: 0 = unlimited)
  onResult?: (result: PingResult, pingCount: number) => void;
  onError?: (error: Error) => void;
}
```

**Returns:** `() => void` - Function to stop pinging

**Example:**
```typescript
import { keepPinging } from './src/keepPinging';

const stopPinging = keepPinging({
  url: 'https://www.example.com',
  frequency: 5, // 5 pings per second
  maxPings: 100, // Stop after 100 pings
  onResult: (result, count) => {
    console.log(`Ping ${count}: ${result.success ? 'OK' : 'FAILED'}`);
  }
});

// Stop pinging manually
setTimeout(() => {
  stopPinging();
}, 10000); // Stop after 10 seconds
```

## Project Structure

```
pingpong/
├── src/
│   ├── index.ts          # Main entry point
│   ├── ping.ts           # pingWeb function
│   └── keepPinging.ts    # keepPinging function
├── test/
│   ├── ping.test.ts      # Tests for pingWeb
│   └── keepPinging.test.ts # Tests for keepPinging
├── dist/                 # Compiled JavaScript (generated)
├── coverage/             # Test coverage reports (generated)
├── package.json
├── tsconfig.json
├── jest.config.js
├── .eslintrc.js
├── .eslintignore
└── README.md
```

## Scripts

### Build & Run
- `npm run build` - Compile TypeScript to JavaScript once
- `npm run build:watch` - Auto-rebuild TypeScript on file changes
- `npm start` - Run the compiled application once
- `npm run start:watch` - Auto-restart compiled app when dist/ files change

### Development
- `npm run dev` - Run in development mode with ts-node (once)
- `npm run dev:watch` - Run in development mode with auto-restart on src/ changes
- `npm run watch` - Run both build:watch and start:watch concurrently

### Testing & Quality
- `npm test` - Run unit tests once
- `npm run test:watch` - Run tests in watch mode
- `npm run lint` - Check for linting issues
- `npm run lint:fix` - Fix linting issues automatically

## Default Behavior

When you run the application, it will:

1. Start pinging https://www.yahoo.com
2. Ping 10 times per second
3. Display real-time results for each ping
4. Show statistics every 50 pings
5. Handle Ctrl+C gracefully and show final statistics

## License

ISC
