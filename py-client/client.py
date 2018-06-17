import socket
import struct

from commands_pb2 import Command, Quit


UNIX_SOCKET_PATH = "/tmp/arr-torrent-cmd-srv.sock"


cmd = Command()
cmd.quit.CopyFrom(Quit())

payload = cmd.SerializeToString()
length = len(payload)

print("payload:", payload)
print("length: ", length)

msg = struct.pack("!L%ds" % length, length, payload)

print("packed: ", msg)

with socket.socket(socket.AF_UNIX, socket.SOCK_STREAM) as s:
    s.connect(UNIX_SOCKET_PATH)
    s.sendall(msg)
