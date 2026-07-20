import { useState } from 'react';
import { Panel, PanelGroup, PanelResizeHandle } from 'react-resizable-panels';
import { useVsCodeApi } from './hooks/useVsCodeApi';
import { useSpans } from './hooks/useSpans';
import { Timeline } from './timeline/Timeline';
import { ConversationSelector } from './components/ConversationSelector';
import { Inspector } from './inspector/Inspector';

export function App() {
  const vscodeApi = useVsCodeApi();
  const { conversations, activeConversationId, data, isLoading, error, selectConversation } = useSpans(vscodeApi as any);
  
  const [selectedIndex, setSelectedIndex] = useState<number | null>(null);

  const selectedSpan = selectedIndex !== null ? data.spans[selectedIndex] : null;
  const selectedToolCalls = selectedSpan ? data.toolCalls.filter(t => t.stepIndex === selectedSpan.stepIndex) : [];
  const selectedFileAccesses = selectedSpan ? data.fileAccesses.filter(f => f.stepIndex === selectedSpan.stepIndex) : [];

  return (
    <div className="panel-layout">
      <div className="panel-header">
        <span className="panel-header-title">Antigravity Tracer</span>
        <span className="span-count">
          {data.spans.length > 0 ? `${data.spans.length} steps` : ''}
        </span>
      </div>
      <ConversationSelector
        conversations={conversations}
        activeConversationId={activeConversationId}
        onSelect={selectConversation}
      />
      <div style={{ flex: 1, overflow: 'hidden' }}>
        {error ? (
          <div className="empty-state">
            <div className="empty-state-icon">⚠️</div>
            <div className="empty-state-text">{error}</div>
          </div>
        ) : isLoading ? (
          <div className="empty-state">
            <div className="empty-state-text">Loading...</div>
          </div>
        ) : (
          <PanelGroup direction="horizontal">
            <Panel defaultSize={50} minSize={20}>
              <Timeline
                spans={data.spans}
                toolCalls={data.toolCalls}
                fileAccesses={data.fileAccesses}
                selectedIndex={selectedIndex}
                onSelect={setSelectedIndex}
              />
            </Panel>
            
            {selectedSpan && (
              <>
                <PanelResizeHandle className="resize-handle" />
                <Panel defaultSize={50} minSize={20}>
                  <Inspector
                    span={selectedSpan}
                    toolCalls={selectedToolCalls}
                    fileAccesses={selectedFileAccesses}
                  />
                </Panel>
              </>
            )}
          </PanelGroup>
        )}
      </div>
    </div>
  );
}
