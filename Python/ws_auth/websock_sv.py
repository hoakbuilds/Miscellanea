import asyncio
import websockets
import sys
import secrets
import json

async def server (websocket, path):
    async for message in websocket:
        msg = json.loads(message)
        if msg['message'] == 'token':

            print(msg)
            obj = { 'token' : secrets.token_hex(64) }

            await websocket.send(json.dumps(obj))
        elif msg['message'] == 'auth':
            print(msg)

            await websocket.send("Hello " + json.dumps(msg['username']))

asyncio.get_event_loop().run_until_complete(websockets.serve(server, 'localhost', 8765))
asyncio.get_event_loop().run_forever()