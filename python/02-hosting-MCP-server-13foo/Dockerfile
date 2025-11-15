FROM ghcr.io/astral-sh/uv:python3.12-bookworm-slim
WORKDIR /app

# Configure UV for container environment
ENV UV_SYSTEM_PYTHON=1 UV_COMPILE_BYTECODE=1



# Copy local wheel file
COPY /Users/lukezha/github/otel-python/adot-python-v0.13-foo/aws-otel-python-instrumentation/dist/aws_opentelemetry_distro-0.13.0-py3-none-any.whl /tmp/

COPY requirements.txt requirements.txt
# Install from requirements file
RUN uv pip install -r requirements.txt

# Install local aws-opentelemetry-distro wheel
RUN uv pip install /tmp/aws_opentelemetry_distro-0.13.0-py3-none-any.whl


# Set AWS region environment variable

ENV AWS_REGION=us-east-1
ENV AWS_DEFAULT_REGION=us-east-1


# Signal that this is running in Docker for host binding logic
ENV DOCKER_CONTAINER=1

# Create non-root user
RUN useradd -m -u 1000 bedrock_agentcore
USER bedrock_agentcore

EXPOSE 8080
EXPOSE 8000

# Copy entire project (respecting .dockerignore)
COPY . .

# Use the full module path

CMD ["opentelemetry-instrument", "python", "-m", "mcp_server"]
