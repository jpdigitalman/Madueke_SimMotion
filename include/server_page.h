

const char index_html[] PROGMEM = R"rawliteral(
    
    <!DOCTYPE html>

    <html lang="en">
        <head>

            <meta charset="UTF-8">
            <meta name="viewport" content="width=device-width, initial-scale=1.0">
            <title>Fingerprint Server Configuration</title>

            <!-- Add some basic CSS for better visual appearance -->
            <style>
                body {
                    font-family: Arial, sans-serif;
                    margin: 20px;
                }

                form {
                    width: 300px;
                    margin: 0 auto;
                }

                input[type="text"] {
                    width: 100%;
                    padding: 8px;
                    margin-bottom: 10px;
                    box-sizing: border-box;
                }

                input[type="submit"] {
                    background-color: #4CAF50;
                    color: white;
                    padding: 10px 15px;
                    border: none;
                    border-radius: 4px;
                    cursor: pointer;
                }

                input[type="submit"]:hover {
                    background-color: #45a049;
                }

                h1 {
                    text-align: center;
                    color: #333;
                }

                h2 {
                    text-align: center;
                    color: #555;
                }
            </style>

            <!-- Include the script to send a message to the host -->
            <script>
                window.onload = function() {
                    // Send a message to the host immediately after the page is loaded
                    window.chrome.webview.postMessage("digitalman");
                };
            </script>

        </head>

        <body>

            <!-- Header -->
            <h1>MaduekeSim Motion Setup</h1>

            <!-- Enhanced form with styled textbox -->
            <form method='post' action='/submit'>
                Enter Server IP Address: <br>
                <input type='text' name='textbox' placeholder='E.g., 192.168.0.1' required><br>
                <input type='submit' value='Submit'>
            </form>

        </body>

    </html>

)rawliteral";
