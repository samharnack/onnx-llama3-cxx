# LLama-3 w/ ONNX and C++

You'll need docker installed, then shell into the docker container:

```bash
docker-compose run --rm app bash
```

Once in the container, download the model:

```bash
huggingface-cli download \
  Nweder/llama-3-onnx \
  --include llama-3-int4-onnx-cpu/* \
  --local-dir model/llama-3-onnx
```

Then run the chat interface:

```bash
./bin/cli chat model/llama-3-onnx/llama-3-int4-onnx-cpu
```

Type `quit()` or press `Ctrl+C` to exit.

## Building

To build the project, run `./dev.sh` from within the docker container.
