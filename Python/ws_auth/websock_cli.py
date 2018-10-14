import asyncio
import websockets
import sys
import json


async def hello_world(uri):
    async with websockets.connect(uri) as websocket:
        token_obj = {
            'message' : "token"
        }
        await websocket.send(json.dumps(token_obj))
        response = await websocket.recv()
        print(response)
        resp = json.loads(response)
        print("Would you like to auth? Type a name:")
        name = input(">> ")
        obj = {
            'message' : 'auth',
            'username' : name,
            'token' : resp['token']
        }
        await websocket.send(json.dumps(obj))
        response = await websocket.recv()
        print(response)

asyncio.get_event_loop().run_until_complete(hello_world('ws://localhost:8765'))
