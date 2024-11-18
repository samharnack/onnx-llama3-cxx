ARG PYTHON_VERSION=3.11

FROM python:${PYTHON_VERSION}-slim

RUN apt-get update && \
    apt-get install -y \
    build-essential \
    python3-dev \
    git \
    cmake \
    bash \
    curl \
    libcurl4-openssl-dev \
    libzip-dev 

RUN pip install "huggingface_hub[cli]"

WORKDIR /src

ENV ORTGENAI_LOG_ORT_LIB=1
ENV ONNXRUNTIME_VERSION=1.20.0
ENV ONNXRUNTIME_ARCH=linux-x64
ENV ONNXRUNTIME_GENAI_VERSION=0.5.1
ENV ONNXRUNTIME_NAME=onnxruntime-${ONNXRUNTIME_ARCH}-${ONNXRUNTIME_VERSION}
ENV ONNXRUNTIME_GENAI_NAME=onnxruntime-genai-${ONNXRUNTIME_GENAI_VERSION}-${ONNXRUNTIME_ARCH}
ENV LD_LIBRARY_PATH=/src/runtime/${ONNXRUNTIME_NAME}/lib:${LD_LIBRARY_PATH}

RUN mkdir -p runtime

RUN cd runtime && \
    curl -L https://github.com/microsoft/onnxruntime/releases/download/v${ONNXRUNTIME_VERSION}/${ONNXRUNTIME_NAME}.tgz \
      -o ${ONNXRUNTIME_NAME}.tgz && \
    tar -xzf ${ONNXRUNTIME_NAME}.tgz && \
    rm ${ONNXRUNTIME_NAME}.tgz

RUN cd runtime && \
    curl -L https://github.com/microsoft/onnxruntime-genai/releases/download/v${ONNXRUNTIME_GENAI_VERSION}/${ONNXRUNTIME_GENAI_NAME}.tar.gz \
      -o ${ONNXRUNTIME_GENAI_NAME}.tar.gz && \
    tar -xzf ${ONNXRUNTIME_GENAI_NAME}.tar.gz && \
    rm ${ONNXRUNTIME_GENAI_NAME}.tar.gz


