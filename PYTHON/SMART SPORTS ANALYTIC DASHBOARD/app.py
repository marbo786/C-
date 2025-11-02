import dash
from dash import dcc, html, Input, Output, State, ALL
import dash_bootstrap_components as dbc
import base64
import io
import pandas as pd
from dash.exceptions import PreventUpdate

# Import our custom modules
from data_processor import DataProcessor
from sports_regressor import SportsRegressor
from sports_chatbot import SportsChatbot

# Initialize components
data_processor = DataProcessor()
regressor = SportsRegressor()
chatbot = SportsChatbot()

# Connect chatbot to data and model
chatbot.connect_to_data(data_processor)
chatbot.connect_to_model(regressor)

# Initialize the Dash app
app = dash.Dash(__name__, external_stylesheets=[dbc.themes.BOOTSTRAP])

# Define the layout with primary sections
app.layout = dbc.Container([
    # Header
    dbc.Row([
        dbc.Col([
            html.H1("Smart Sports Analytics Dashboard", className="text-center mb-4"),
            html.Hr()
        ], width=12)
    ]),
    
    # Data Upload Section
    dbc.Row([
        dbc.Col([
            dbc.Card([
                dbc.CardHeader("Upload Sports Data"),
                dbc.CardBody([
                    dcc.Upload(
                        id='upload-data',
                        children=html.Div([
                            'Drag and Drop or ',
                            html.A('Select CSV File')
                        ]),
                        style={
                            'width': '100%',
                            'height': '60px',
                            'lineHeight': '60px',
                            'borderWidth': '1px',
                            'borderStyle': 'dashed',
                            'borderRadius': '5px',
                            'textAlign': 'center',
                            'margin': '10px'
                        },
                        multiple=False
                    ),
                    html.Div(id='output-data-upload'),
                ])
            ], className="mb-4")
        ], width=12)
    ]),
    
    # Analysis Tabs (Visualization and ML)
    dbc.Row([
        dbc.Col([
            dbc.Tabs([
                dbc.Tab(label="Data Visualization", tab_id="visualization-tab", children=[
                    dbc.Row([
                        dbc.Col([
                            html.Label("Chart Type"),
                            dcc.Dropdown(
                                id='chart-type',
                                options=[
                                    {'label': 'Bar Chart', 'value': 'bar'},
                                    {'label': 'Line Chart', 'value': 'line'},
                                    {'label': 'Scatter Plot', 'value': 'scatter'}
                                ],
                                value='bar'
                            )
                        ], width=6),
                        dbc.Col([
                            html.Label("X-Axis"),
                            dcc.Dropdown(id='x-axis')
                        ], width=6)
                    ]),
                    dbc.Row([
                        dbc.Col([
                            html.Label("Y-Axis"),
                            dcc.Dropdown(id='y-axis')
                        ], width=6),
                        dbc.Col([
                            html.Label("Color By (Optional)"),
                            dcc.Dropdown(id='color-by')
                        ], width=6)
                    ]),
                    dbc.Button("Update Chart", color="success", id="update-chart-button", className="mt-2"),
                    dcc.Graph(id='visualization-graph')
                ]),
                dbc.Tab(label="Regression Modeling", tab_id="modeling-tab", children=[
                    dbc.Row([
                        dbc.Col([
                            html.Label("Target Variable"),
                            dcc.Dropdown(id='target-variable')
                        ], width=6),
                        dbc.Col([
                            html.Label("Model Type"),
                            dcc.Dropdown(
                                id='model-type',
                                options=[
                                    {'label': 'Linear Regression', 'value': 'linear'}
                                ],
                                value='linear',
                                disabled=True
                            )
                        ], width=6)
                    ]),
                    html.Label("Feature Variables"),
                    dcc.Dropdown(id='feature-variables', multi=True),
                    dbc.Button("Train Model", color="primary", id="train-model-button", className="mt-2"),
                    html.Div(id='model-metrics', className="mt-3"),
                    html.Hr(),
                    html.H5("Make Predictions"),
                    html.Div(id='prediction-inputs'),
                    dbc.Button("Predict", color="warning", id="predict-button", className="mt-2"),
                    html.Div(id='prediction-output', className="mt-3")
                ])
            ], id="tabs", active_tab="visualization-tab")
        ], width=12)
    ]),
    
    # Chatbot Section - Enhanced UI
    dbc.Row([
        dbc.Col([
            dbc.Card([
                dbc.CardHeader([
                    html.H4("Marbo - Sports Analytics Assistant", className="mb-0"),
                    html.Small("Ask questions about your sports data")
                ]),
                dbc.CardBody([
                    # Chat history area
                    html.Div(
                        id="chatbot-output",
                        className="chat-history p-3 border rounded",
                        style={
                            'maxHeight': '300px',
                            'overflowY': 'auto',
                            'marginBottom': '15px'
                        }
                    ),
                    
                    # Input area
                    dbc.InputGroup([
                        dbc.Input(
                            id="chatbot-input",
                            type="text",
                            placeholder="Ask Marbo about your sports data...",
                            debounce=True
                        ),
                        dbc.Button("Send", id="chatbot-button", color="info", n_clicks=0)
                    ])
                ]),
                dbc.CardFooter([
                    html.Small([
                        "Example questions: ",
                        html.Span("'Show me data summary'", className="text-info mr-2"),
                        html.Span("'What's my model accuracy?'", className="text-info mr-2"),
                        html.Span("'Help with visualization'", className="text-info")
                    ])
                ])
            ], className="mt-4 mb-4")
        ], width=12)
    ])
], fluid=True)

# Callback for data upload
@app.callback(
    [
        Output('output-data-upload', 'children'),
        Output('x-axis', 'options'),
        Output('y-axis', 'options'),
        Output('color-by', 'options'),
        Output('target-variable', 'options'),
        Output('feature-variables', 'options')
    ],
    Input('upload-data', 'contents'),
    State('upload-data', 'filename'),
    prevent_initial_call=True
)
def update_components(contents, filename):
    if not contents:
        raise PreventUpdate
    
    try:
        content_type, content_string = contents.split(',')
        decoded = base64.b64decode(content_string)
        
        if 'csv' in filename:
            # Load and process data
            raw_df = data_processor.load_data(io.StringIO(decoded.decode('utf-8')))
            processed_cols = data_processor.get_processed_columns()
            
            raw_options = [{'label': col, 'value': col} for col in raw_df.columns]
            proc_options = [{'label': col, 'value': col} for col in processed_cols]
            
            return [
                html.Div([
                    html.H5(f'Uploaded: {filename}'),
                    dbc.Table.from_dataframe(raw_df.head(3)), 
                ]),
                raw_options,  # x-axis
                raw_options,  # y-axis
                raw_options,  # color-by
                raw_options,  # target-variable - Changed to raw columns for consistency
                proc_options   # feature-variables
            ]
            
    except Exception as e:
        return [
            html.Div(f"Error: {str(e)}"), 
            [], [], [], [], []
        ]

# Callback for chatbot interaction
@app.callback(
    Output('chatbot-output', 'children'),
    [Input('chatbot-button', 'n_clicks'),
     Input('chatbot-input', 'n_submit')],
    [State('chatbot-input', 'value'),
     State('chatbot-output', 'children')]
)
def update_chatbot_response(n_clicks, n_submit, query, existing_output):
    
    # Check which input triggered the callback
    ctx = dash.callback_context
    if not ctx.triggered:
        raise PreventUpdate
        
    trigger = ctx.triggered[0]['prop_id']
    
    if (trigger == 'chatbot-button.n_clicks' or trigger == 'chatbot-input.n_submit') and query:
        response = chatbot.get_response(query)
        
        # Create a new conversation entry
        new_entry = html.Div([
            html.P(f"You: {query}", className="user-msg"),
            html.P(f"Marbo: {response}", className="bot-msg")
        ])
        
        # If there's existing output, append to it, otherwise create new
        if existing_output:
            if isinstance(existing_output, list):
                return existing_output + [new_entry]
            else:
                return [existing_output, new_entry]
        else:
            return [new_entry]
    
    raise PreventUpdate

# Callback to clear chatbot input after sending
@app.callback(
    Output('chatbot-input', 'value'),
    [Input('chatbot-button', 'n_clicks'),
     Input('chatbot-input', 'n_submit')]
)
def clear_chatbot_input(n_clicks, n_submit):
    ctx = dash.callback_context
    if ctx.triggered and (ctx.triggered[0]['prop_id'] == 'chatbot-button.n_clicks' or 
                         ctx.triggered[0]['prop_id'] == 'chatbot-input.n_submit'):
        return ''
    raise PreventUpdate

# Callback for visualization
@app.callback(
    Output('visualization-graph', 'figure'),
    [Input('update-chart-button', 'n_clicks')],
    [State('chart-type', 'value'),
     State('x-axis', 'value'),
     State('y-axis', 'value'),
     State('color-by', 'value')]
)
def update_graph(n_clicks, chart_type, x_col, y_col, color_col):
    if n_clicks is None or x_col is None or y_col is None:
        raise PreventUpdate
    
    if data_processor.raw_data is None:
        raise PreventUpdate
    
    df = data_processor.raw_data

    trace = {
        'x': df[x_col],
        'y': df[y_col],
        'type': chart_type,
        'mode': 'markers' if chart_type == 'scatter' else 'lines' if chart_type == 'line' else None
    }
    
    if color_col:
        trace['marker'] = {'color': df[color_col]}
    
    fig = {
        'data': [trace],
        'layout': {
            'title': f'{chart_type.capitalize()} of {y_col} vs {x_col}',
            'xaxis': {'title': x_col},
            'yaxis': {'title': y_col}
        }
    }
    
    return fig

# Callback for model training
@app.callback(
    Output('model-metrics', 'children'),
    [Input('train-model-button', 'n_clicks')],
    [State('target-variable', 'value'),
     State('feature-variables', 'value'),
     State('model-type', 'value')]
)
def train_model(n_clicks, target, features, model_type):
    if n_clicks is None or not target or not features:
        raise PreventUpdate
    
    try:
        # Prepare data
        # Use raw data instead of processed data for training
        # Since target-variable was changed to raw columns
        processed_data = data_processor.processed_data
        
        # Ensure target is in processed data
        if target not in data_processor.raw_data.columns:
            return html.Div([
                html.H5("Error training model"),
                html.P(f"Target column '{target}' not found in data")
            ])
            
        # Get target from raw data and add it to processed data for training
        processed_data[target] = data_processor.raw_data[target]
        
        # Train the model
        regressor.prepare_data(processed_data, target)
        regressor.train(model_type)
        
        # Evaluate model
        metrics = regressor.evaluate()
        
        # Update chatbot with metrics
        metrics_interpretation = chatbot.interpret_metrics(metrics)
        
        return html.Div([
            html.H5("Linear Regression Model Metrics"),
            html.P(f"R² Score: {metrics['R²']:.4f}"),
            html.P(f"RMSE: {metrics['RMSE']:.4f}"),
            html.P(f"MAE: {metrics['MAE']:.4f}"),
            html.P(metrics_interpretation)
        ])
    except Exception as e:
        return html.Div([
            html.H5("Error training model"),
            html.P(str(e))
        ])

# Callback for prediction inputs
@app.callback(
    Output('prediction-inputs', 'children'),
    [Input('train-model-button', 'n_clicks')],
    [State('feature-variables', 'value')]
)
def create_prediction_inputs(n_clicks, features):
    if n_clicks is None or not features:
        raise PreventUpdate
    
    inputs = []
    for feature in features:
        inputs.append(
            dbc.Row([  # Changed from FormGroup to Row/Col
                dbc.Col([
                    dbc.Label(feature),
                    dbc.Input(id={'type': 'pred-input', 'index': feature}, type='number')
                ], width=6)
            ], className="mb-2")  # Added some spacing
        )
    
    return inputs

# Callback for making predictions
@app.callback(
    Output('prediction-output', 'children'),
    [Input('predict-button', 'n_clicks')],
    [
        State('feature-variables', 'value'),
        State({'type': 'pred-input', 'index': ALL}, 'value')
    ]
)
def make_prediction(n_clicks, features, pred_values):
    if n_clicks is None or not features or None in pred_values:
        raise PreventUpdate
    
    try:
        # Create input dictionary
        input_data = {feature: [value] for feature, value in zip(features, pred_values)}
        df = pd.DataFrame(input_data)
        
        # Make prediction
        prediction = regressor.predict(df)
        
        return html.Div([
            html.H5("Prediction Result"),
            html.P(f"Predicted value: {prediction[0]:.4f}")
        ])
    except Exception as e:
        return html.Div([
            html.H5("Error making prediction"),
            html.P(str(e))
        ])

# Run the app
if __name__ == '__main__':
    app.run(debug=True)