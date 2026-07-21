import { memo } from 'react';
import { Handle, Position, type NodeProps } from '@xyflow/react';
import type { Span } from '@ag-tracer/shared';
import '../styles/timeline.css'; // Reuse timeline styles for badges

export const SpanNode = memo(({ data, selected }: NodeProps) => {
  const span = data.span as Span;
  
  // Choose color based on source/type
  let sourceClass = '';
  if (span.source === 'USER_EXPLICIT') sourceClass = 'timeline-row--user';
  else if (span.source === 'MODEL') sourceClass = 'timeline-row--model';
  else if (span.source === 'SYSTEM') sourceClass = 'timeline-row--system';

  if (span.status === 'ERROR') sourceClass = 'timeline-row--error';

  return (
    <div className={`flow-node ${sourceClass} ${selected ? 'selected' : ''}`} style={nodeStyle}>
      <Handle type="target" position={Position.Top} />
      <div style={headerStyle}>
        <span className="timeline-step-index">#{span.stepIndex}</span>
        <span className="timeline-type-badge">{span.type}</span>
      </div>
      <div style={contentStyle}>
        {span.source === 'USER_EXPLICIT' ? 'User Request' : 
         span.type === 'PLANNER_RESPONSE' ? 'Thinking...' : 
         span.content || 'System Step'}
      </div>
      <Handle type="source" position={Position.Bottom} />
      <Handle type="source" position={Position.Right} id="tools" />
    </div>
  );
});

const nodeStyle: React.CSSProperties = {
  background: 'var(--vscode-editor-background)',
  border: '1px solid var(--vscode-widget-border, rgba(128, 128, 128, 0.2))',
  borderRadius: '4px',
  padding: '8px',
  minWidth: '200px',
  maxWidth: '250px',
  boxShadow: '0 2px 4px rgba(0,0,0,0.1)',
};

const headerStyle: React.CSSProperties = {
  display: 'flex',
  justifyContent: 'space-between',
  alignItems: 'center',
  marginBottom: '8px',
  gap: '8px',
};

const contentStyle: React.CSSProperties = {
  fontSize: 'var(--text-sm)',
  color: 'var(--vscode-editor-foreground)',
  whiteSpace: 'nowrap',
  overflow: 'hidden',
  textOverflow: 'ellipsis',
};
