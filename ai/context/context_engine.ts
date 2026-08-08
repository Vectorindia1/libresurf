// ai/context/context_engine.ts
// AI Context Engine
//
// Responsible for extracting and sanitizing browser state before sending it
// to an AI provider. Ensures that credentials, cookies, and other sensitive
// data are stripped from the context.

export interface PageContext {
  url: string;
  title: string;
  visibleText: string;
  selectedText?: string;
  metadata: Record<string, string>;
  relevantLinks?: Array<{ text: string; url: string }>;
}

export class ContextEngine {
  /**
   * Builds a safe context object from the current state of a browser tab.
   * This is a stub implementation. In reality, it would communicate via IPC
   * to the browser core to fetch the sanitized DOM text.
   */
  public async buildPageContext(tabId: number): Promise<PageContext> {
    // TODO: fetch actual tab context via IPC
    return {
      url: 'https://example.com',
      title: 'Example Domain',
      visibleText: this.sanitize('This domain is for use in illustrative examples...'),
      metadata: {},
    };
  }

  /**
   * Sanitizes raw text content before sending it to an AI provider.
   * Removes identifiable sensitive fields like cookies and API keys.
   */
  public sanitize(raw: string): string {
    let sanitized = raw;
    
    // Remove common sensitive header formats
    sanitized = sanitized.replace(/cookie:\s*[^\n]*/gi, '[REDACTED_COOKIE]');
    sanitized = sanitized.replace(/authorization:\s*bearer\s+[^\n]*/gi, '[REDACTED_TOKEN]');
    
    // Naive regex to remove potential API keys and passwords
    // Note: a robust implementation requires a more sophisticated parsing strategy.
    sanitized = sanitized.replace(/(api_key|apikey|password|secret)["']?\s*[:=]\s*["']?[\w-]{8,}["']?/gi, '$1=[REDACTED]');
    
    return sanitized;
  }
}
