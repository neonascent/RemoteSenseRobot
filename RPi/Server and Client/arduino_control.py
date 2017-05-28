# telnet program example
import socket, select, string, sys, serial, re
 
def prompt() :
    sys.stdout.write('<You> ')
    sys.stdout.flush()
 
#main function
if __name__ == "__main__":
     
    if(len(sys.argv) < 3) :
        print 'Usage : python telnet.py hostname port'
        sys.exit()
     
    host = sys.argv[1]
    port = int(sys.argv[2])
    
    try : 
        
        arduino = serial.Serial('/dev/ttyUSB0', 115200)
        
    except :
        print 'failed to connect to Arduino'
        sys.exit()
    
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.settimeout(2)
     
    # connect to remote host
    try :
        s.connect((host, port))
    except :
        print 'Unable to connect'
        sys.exit()
     
    print 'Connected to remote host.'
     
    while 1:
        socket_list = [sys.stdin, s]
         
        # Get the list sockets which are readable
        read_sockets, write_sockets, error_sockets = select.select(socket_list , [], [])
         
        for sock in read_sockets:
            #incoming message from remote server
            if sock == s:
                data = sock.recv(4096)
                if not data :
                    print '\nDisconnected from chat server'
                    sys.exit()
                else :
                    #print data
                    nonsystemdata = re.sub("[\(\[].*?[\)\]]", "", data)
                    cleardata = re.sub('[^a-zA-Z0-9$.]', '', nonsystemdata)
                    sys.stdout.write(cleardata + "\n")
                    arduino.write(cleardata)
                    s.send("received: " + cleardata + "\n")

             
            #user entered a message
            #else :
                #msg = sys.stdin.readline()
                #s.send(msg)
                #prompt()
                