// ai/providers/ai_provider.ts
// Core AI provider abstraction.
//
// All AI providers must implement this interface. The AI Manager interacts
// exclusively through this interface — never through provider-specific APIs.
// This ensures the browser is never tightly coupled to a single AI vendor.

export interface ChatMessage {
  role: 'system' | 'user' | 'assistant';
  content: string;
}

export interface ChatOptions {
  model?: string;
  temperature?: number;
  maxTokens?: number;
  stream?: boolean;
}

export interface ChatResponse {
  content: string;
  model: string;
  usage?: {
    promptTokens: number;
    completionTokens: number;
    totalTokens: number;
  };
}

export interface ProviderCapabilities {
  streaming: boolean;
  embeddings: boolean;
  maxContextTokens: number;
  models: string[];
}

/**
 * Abstract AI provider interface.
 *
 * Implementations: OpenAICompatibleProvider, AnthropicProvider,
 * GeminiProvider, OllamaProvider, CustomEndpointProvider.
 */
export interface AIProvider {
  readonly id: string;
  readonly name: string;

  /** Send a chat request and return the full response. */
  chat(messages: ChatMessage[], options?: ChatOptions): Promise<ChatResponse>;

  /** Send a chat request and stream tokens as they arrive. */
  stream(messages: ChatMessage[], options?: ChatOptions): AsyncIterable<string>;

  /** Generate embeddings for the given texts. Optional. */
  embeddings?(texts: string[]): Promise<number[][]>;

  /** Return the capabilities of this provider/model. */
  capabilities(): ProviderCapabilities;

  /** Validate that credentials are set and the provider is reachable. */
  validate(): Promise<{ ok: boolean; error?: string }>;
}

/**
 * Registry of all configured AI providers.
 * The active provider is selected by the user in Settings → AI → Providers.
 */
export class AIProviderRegistry {
  private providers = new Map<string, AIProvider>();
  private activeProviderId: string | null = null;

  register(provider: AIProvider): void {
    this.providers.set(provider.id, provider);
  }

  setActive(providerId: string): void {
    if (!this.providers.has(providerId)) {
      throw new Error(`Provider not found: ${providerId}`);
    }
    this.activeProviderId = providerId;
  }

  getActive(): AIProvider {
    if (!this.activeProviderId) {
      throw new Error('No AI provider configured. Go to Settings → AI → Providers.');
    }
    const provider = this.providers.get(this.activeProviderId);
    if (!provider) throw new Error(`Active provider not found: ${this.activeProviderId}`);
    return provider;
  }

  getAll(): AIProvider[] {
    return Array.from(this.providers.values());
  }
}
