// ai/agent/agent.ts
// AI Agent
//
// Orchestrates AI interactions, providing the model with access to browser
// tools according to strict permission levels.

import { AIProvider, ChatMessage } from '../providers/ai_provider';
import { ContextEngine } from '../context/context_engine';
import { buildSystemPrompt, wrapPageContent } from '../safety/safety_layer';

export interface AgentOptions {
  provider: AIProvider;
  contextEngine: ContextEngine;
}

export type PermissionLevel = 0 | 1 | 2;

export interface BrowserTool {
  name: string;
  description: string;
  level: PermissionLevel;
  execute: (args: Record<string, any>) => Promise<any>;
}

export class AIAgent {
  private provider: AIProvider;
  private contextEngine: ContextEngine;
  private tools: Map<string, BrowserTool> = new Map();

  constructor(options: AgentOptions) {
    this.provider = options.provider;
    this.contextEngine = options.contextEngine;
    this.registerDefaultTools();
  }

  private registerDefaultTools() {
    // Level 0 (Read-only)
    this.registerTool({
      name: 'getCurrentPage',
      description: 'Returns the sanitized text content and metadata of the active tab.',
      level: 0,
      execute: async () => this.contextEngine.buildPageContext(1) // Stub tab ID
    });

    // Level 1 (Navigation)
    this.registerTool({
      name: 'openTab',
      description: 'Opens a new browser tab with the specified URL.',
      level: 1,
      execute: async (args) => { /* TODO: IPC to browser core */ return { success: true }; }
    });

    // Level 2 (External side effects - requires confirmation)
    this.registerTool({
      name: 'downloadFile',
      description: 'Downloads a file from a URL to the local disk.',
      level: 2,
      execute: async (args) => {
        // TODO: UI Confirmation flow goes here before IPC to browser core
        return { status: 'pending_confirmation' };
      }
    });
  }

  public registerTool(tool: BrowserTool) {
    this.tools.set(tool.name, tool);
  }

  public async chat(userMessage: string, includePageContext: boolean = false): Promise<string> {
    const messages: ChatMessage[] = [
      { role: 'system', content: buildSystemPrompt() }
    ];

    if (includePageContext) {
      const context = await this.contextEngine.buildPageContext(1);
      messages.push({
        role: 'user',
        content: `Current page context:\n${wrapPageContent(context.visibleText)}`
      });
    }

    messages.push({ role: 'user', content: userMessage });

    // In a full implementation, we'd pass tool schemas to the provider here.
    const response = await this.provider.chat(messages);
    return response.content;
  }
}
