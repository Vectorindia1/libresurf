# Contributing to LibreSurf

Thank you for considering contributing. LibreSurf is open source and welcomes contributions of all kinds.

---

## Code of Conduct

Please read [CODE_OF_CONDUCT.md](CODE_OF_CONDUCT.md) before participating.

---

## How to Contribute

### Reporting Bugs

Open a GitHub Issue with label `bug`. Include:
- OS and version
- Steps to reproduce
- Expected vs. actual behavior
- Logs or screenshots if applicable

For **security issues**, see [SECURITY.md](SECURITY.md) — do NOT open a public issue.

### Feature Requests

Open a GitHub Issue with label `feature`. Describe:
- What you want to do
- Why it matters for users
- Any implementation ideas

### Pull Requests

1. Fork the repository
2. Create a branch: `feature/your-feature` or `fix/your-bug`
3. Make your changes
4. Ensure tests pass: `cmake --build build && ctest --test-dir build`
5. Ensure lint passes: `npm run lint && npm run format:check`
6. Open a PR targeting `develop`

---

## Branch Naming

| Type | Pattern |
|---|---|
| Feature | `feature/short-description` |
| Bug fix | `fix/short-description` |
| Security | `security/short-description` |
| Docs | `docs/short-description` |

---

## Commit Format

```
type(scope): short description

body (optional)

Closes #issue-number
```

Types: `feat`, `fix`, `docs`, `refactor`, `test`, `chore`, `security`

Example:
```
feat(proxy): add SOCKS5 authentication support

Implements username/password auth for SOCKS5 proxies.
Credentials stored in OS keychain, never plaintext.

Closes #63
```

---

## Code Standards

### C++

- C++17
- clang-format (Google style, see `.clang-format`)
- No raw `new`/`delete` — use smart pointers
- All public APIs must have Doxygen comments
- CEF objects via `CefRefPtr<>`

### TypeScript

- Strict mode enabled
- No `any` types
- Prettier + ESLint enforced
- All async functions typed

### Testing

- Every new feature needs unit tests
- Every bug fix needs a regression test
- Security changes need security tests in `tests/security/`

---

## Good First Issues

Look for issues labeled `good-first-issue`. These are scoped, well-defined, and don't require deep knowledge of the codebase.

---

## Questions

Open a GitHub Discussion or reach out in the project's community channels.
