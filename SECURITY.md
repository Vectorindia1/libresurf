# Security Policy

## Supported Versions

| Version | Supported |
|---|---|
| `main` (development) | ✅ |
| Tagged releases | ✅ |

## Reporting a Vulnerability

**Do NOT open a public GitHub Issue for security vulnerabilities.**

Please report security issues by emailing:

```
security@libresurf.org   (replace with actual contact before release)
```

Include:
- Description of the vulnerability
- Steps to reproduce
- Potential impact
- Suggested fix (if any)

You will receive a response within **72 hours**.

## Scope

We consider the following in-scope:

- Proxy / DNS leaks
- Tor profile isolation failures
- Prompt injection leading to unauthorized actions
- AI receiving cookies, passwords, or session tokens without consent
- Cross-profile data leakage
- Credential theft from credential store
- Extension sandbox escapes
- Remote code execution
- Memory safety issues in C++ core

## Out of Scope

- Issues in CEF / Chromium itself (report to Chromium security team)
- Issues in bundled third-party libraries (report upstream)
- Social engineering attacks

## Disclosure Policy

We follow **responsible disclosure**:

1. Reporter submits vulnerability privately.
2. We acknowledge within 72 hours.
3. We reproduce and assess severity within 7 days.
4. We develop and test a fix.
5. We release the fix and publish a security advisory.
6. Reporter is credited (if desired).

We aim to fix critical vulnerabilities within **14 days** of confirmation.
