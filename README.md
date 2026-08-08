# LibreSurf

> **Fast, private, transparent, customizable, AI-native, and free/open source.**

LibreSurf is a privacy-first browser built on Chromium (CEF) with a built-in AI platform, modular proxy/Tor networking, and a browser MCP server — giving users complete control over how they access the internet.

[![Build](https://github.com/libresurf/libresurf/actions/workflows/ci.yml/badge.svg)](https://github.com/libresurf/libresurf/actions)
[![License](https://img.shields.io/badge/license-Apache--2.0-blue.svg)](LICENSE)
[![Security Policy](https://img.shields.io/badge/security-policy-green.svg)](SECURITY.md)

---

## Features

| Feature | Status |
|---|---|
| Chromium engine (CEF) | 🚧 In progress |
| Tab management | 🚧 In progress |
| Browser profiles | 🚧 In progress |
| Tracker blocking (EasyList) | 🚧 In progress |
| Cookie controls | 🚧 In progress |
| HTTP / HTTPS / SOCKS4 / SOCKS5 proxy | 🚧 In progress |
| Tor profile | 🚧 In progress |
| DNS-over-HTTPS / DNS-over-TLS | 🚧 In progress |
| Configurable search providers | 🚧 In progress |
| AI sidebar (OpenAI, Anthropic, Gemini, Ollama) | 🚧 In progress |
| AI search with citations | 🚧 In progress |
| AI agent + browser tools | 🚧 In progress |
| Browser MCP server | 🚧 In progress |
| Fingerprint protection | 🚧 In progress |
| No telemetry by default | ✅ |
| No mandatory account | ✅ |
| Open source | ✅ |

---

## Building

See **[docs/building.md](docs/building.md)** for full instructions.

### Quick start (Linux)

```bash
# 1. Clone
git clone https://github.com/libresurf/libresurf.git
cd libresurf

# 2. Install Node dependencies
npm install

# 3. Download CEF prebuilt (see docs/building.md for version)
# Set CEF_ROOT to the extracted directory

# 4. Configure + build
cmake -B build -DCEF_ROOT=/path/to/cef_binary
cmake --build build --parallel

# 5. Run
./build/bin/libresurf
```

---

## Privacy Principles

```
No telemetry by default
No mandatory account
No unnecessary cloud services
No hidden analytics
No advertising SDKs
```

---

## Architecture

See [ARCHITECTURE.md](ARCHITECTURE.md).

---

## Contributing

See [CONTRIBUTING.md](CONTRIBUTING.md). All contributions welcome.

---

## Security

See [SECURITY.md](SECURITY.md) for vulnerability reporting.

---

## License

Apache-2.0. See [LICENSE](LICENSE).
