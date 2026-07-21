import { useCallback } from 'react';
import { Panel, PanelGroup, PanelResizeHandle } from 'react-resizable-panels';
import { useVsCodeApi } from './hooks/useVsCodeApi';
import { useSpans } from './hooks/useSpans';
import { Timeline } from './timeline/Timeline';
import { ConversationSelector } from './components/ConversationSelector';
import { Inspector } from './inspector/Inspector';
import { useTracerStore } from './store/useTracerStore';
import { AgentFlow } from './flow/AgentFlow';
import './App.css'; // Let's add some styles for the toggle

export function App() {
  const vscodeApi = useVsCodeApi();
  const { selectConversation } = useSpans(vscodeApi);
  
  const { 
    conversations, 
    activeConversationId, 
    spans, 
    toolCalls, 
    fileAccesses, 
    isLoading, 
    error,
    selectedIndex,
    setSelectedIndex,
    viewMode,
    setViewMode
  } = useTracerStore();

  // Reset selection when conversation changes
  const handleSelectConversation = useCallback((conversationId: string) => {
    selectConversation(conversationId);
  }, [selectConversation]);

  const selectedSpan = selectedIndex !== null ? spans[selectedIndex] ?? null : null;
  const selectedToolCalls = selectedSpan ? toolCalls.filter(t => t.stepIndex === selectedSpan.stepIndex) : [];
  const selectedFileAccesses = selectedSpan ? fileAccesses.filter(f => f.stepIndex === selectedSpan.stepIndex) : [];

  return (
    <div className="panel-layout">
      <div className="panel-header">
        <span className="panel-header-title">Antigravity Tracer</span>
        <div className="panel-header-right">
          <div className="view-toggle">
            <button 
              className={viewMode === 'timeline' ? 'active' : ''} 
              onClick={() => setViewMode('timeline')}
            >
              Timeline
            </button>
            <button 
              className={viewMode === 'flow' ? 'active' : ''} 
              onClick={() => setViewMode('flow')}
            >
              Flow
            </button>
          </div>
          <span className="span-count">
            {spans.length > 0 ? `${spans.length} steps` : ''}
          </span>
        </div>
      </div>
      <ConversationSelector
        conversations={conversations}
        activeConversationId={activeConversationId}
        onSelect={handleSelectConversation}
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
              {viewMode === 'timeline' ? (
                <Timeline
                  spans={spans}
                  toolCalls={toolCalls}
                  fileAccesses={fileAccesses}
                  selectedIndex={selectedIndex}
                  onSelect={setSelectedIndex}
                />
              ) : (
                <AgentFlow />
              )}
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
