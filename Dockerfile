FROM gcc:latest

# 安装必要工具
RUN apt-get update && apt-get install -y \
    make \
    jq \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /workspace
COPY . .

# 验证工具链
RUN echo "环境工具版本：" && \
    gcc --version | head -n1 && \
    make --version | head -n1 && \
    jq --version