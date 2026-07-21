import { useState, useMemo, useEffect } from 'react';
import Editor from '@monaco-editor/react';
import type { Span, ToolCallRecord, FileAccessRecord } from '@ag-tracer/shared';
import './Inspector.css';

interface InspectorProps {
  span: Span;
  toolCalls: ToolCallRecord[];
  fileAccesses: FileAccessRecord[];
}

type TabId = 'content' | 'thinking' | 'tools';

export function Inspector({ span, toolCalls, fileAccesses }: InspectorProps) {
  const hasContent = !!span.content;
  const hasThinking = !!span.thinking;
  const hasTools = toolCalls.length > 0;

  const [activeTab, setActiveTab] = useState<TabId>(() => {
    if (hasContent) return 'content';
    if (hasThinking) return 'thinking';
    if (hasTools) return 'tools';
    return 'content';
  });

  // Correct the active tab when the selected span changes
  useEffect(() => {
    if (activeTab === 'content' && !hasContent) {
      setActiveTab(hasThinking ? 'thinking' : hasTools ? 'tools' : 'content');
    } else if (activeTab === 'thinking' && !hasThinking) {
      setActiveTab(hasContent ? 'content' : hasTools ? 'tools' : 'content');
    } else if (activeTab === 'tools' && !hasTools) {
      setActiveTab(hasContent ? 'content' : hasThinking ? 'thinking' : 'content');
    }
  }, [span.stepIndex, hasContent, hasThinking, hasTools]);

  const toolsJson = useMemo(() => {
    if (!hasTools) return '';
    return JSON.stringify(toolCalls.map(tc => ({ name: tc.toolName, args: tc.toolArgs })), null, 2);
  }, [toolCalls]);

  let editorValue = '';
  let language = 'markdown';

  if (activeTab === 'content') {
    editorValue = span.content || 'No content available.';
  } else if (activeTab === 'thinking') {
    editorValue = span.thinking || 'No thinking available.';
  } else if (activeTab === 'tools') {
    editorValue = toolsJson;
    language = 'json';
  }

  return (
    <div className="inspector">
      <div className="inspector-header">
        <div className="inspector-title">Step {span.stepIndex} ({span.source})</div>
        <div className="inspector-tabs">
          <button 
            className={`inspector-tab ${activeTab === 'content' ? 'active' : ''} ${!hasContent ? 'disabled' : ''}`}
            onClick={() => hasContent && setActiveTab('content')}
            disabled={!hasContent}
          >
            Content
          </button>
          <button 
            className={`inspector-tab ${activeTab === 'thinking' ? 'active' : ''} ${!hasThinking ? 'disabled' : ''}`}
            onClick={() => hasThinking && setActiveTab('thinking')}
            disabled={!hasThinking}
          >
            Thinking
          </button>
          <button 
            className={`inspector-tab ${activeTab === 'tools' ? 'active' : ''} ${!hasTools ? 'disabled' : ''}`}
            onClick={() => hasTools && setActiveTab('tools')}
            disabled={!hasTools}
          >
            Tool Calls ({toolCalls.length})
          </button>
        </div>
      </div>
      <div className="inspector-body">
        <Editor
          key={span.stepIndex}
          height="100%"
          language={language}
          theme="vs-dark"
          value={editorValue}
          loading={<div style={{ padding: '16px', color: 'var(--vscode-descriptionForeground)' }}>Loading editor...</div>}
          options={{
            readOnly: true,
            wordWrap: 'on',
            minimap: { enabled: false },
            scrollBeyondLastLine: false,
            padding: { top: 16, bottom: 16 },
            fontSize: 13,
            lineHeight: 20,
            renderLineHighlight: 'none',
            hideCursorInOverviewRuler: true,
            automaticLayout: true,
            stickyScroll: { enabled: false },
            overviewRulerLanes: 0,
            scrollbar: {
              useShadows: false,
              vertical: 'visible',
              horizontal: 'visible'
            }
          }}
        />
      </div>
    </div>
  );
}
