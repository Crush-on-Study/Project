package chatting;

import java.io.*;
import java.net.*;
import java.util.*;

public class Server {
    private static List<Socket> clients = new ArrayList<>();
    private static List<String> usernames = new ArrayList<>();

    public static void main(String[] args) {
        try {
            // 서버 소켓 생성
            ServerSocket serverSocket = new ServerSocket(12345);
            System.out.println("서버가 시작되었습니다.");

            while (true) {
                // 클라이언트의 연결 요청 대기
                Socket clientSocket = serverSocket.accept();
                clients.add(clientSocket);
                System.out.println("새로운 클라이언트가 연결되었습니다.");

                // 클라이언트와의 통신을 위한 스레드 생성
                Thread thread = new Thread(new ClientHandler(clientSocket));
                thread.start();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    // 클라이언트와의 통신을 처리하는 핸들러
    static class ClientHandler implements Runnable {
        private Socket clientSocket;
        private BufferedReader input;
        private PrintWriter output;
        private String username;

        public ClientHandler(Socket clientSocket) {
            this.clientSocket = clientSocket;
        }

        @Override
        public void run() {
            try {
                // 입력 스트림 생성
                input = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));

                // 출력 스트림 생성
                output = new PrintWriter(clientSocket.getOutputStream(), true);

                // 사용자명 입력 받기
                username = input.readLine();
                usernames.add(username);
                System.out.println(username + " 님이 입장하셨습니다.");

                // 다른 클라이언트에게 입장 메시지 전달
                broadcastMessage(username + " 님이 입장하셨습니다.");

                // 클라이언트로부터의 메시지 수신 및 브로드캐스팅
                String message;
                while ((message = input.readLine()) != null) {
                    System.out.println(username + ": " + message);
                    broadcastMessage(username + ": " + message);

                    // 종료 조건 확인
                    if (message.equals("bye")) {
                        break;
                    }
                }

                // 클라이언트 종료 처리
                clients.remove(clientSocket);
                usernames.remove(username);
                System.out.println(username + " 님이 퇴장하셨습니다.");

                // 다른 클라이언트에게 퇴장 메시지 전달
                broadcastMessage(username + " 님이 퇴장하셨습니다.");

                // 클라이언트 소켓 닫기
                clientSocket.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }

        // 다른 클라이언트에게 메시지 브로드캐스팅
        private void broadcastMessage(String message) {
            for (Socket client : clients) {
                try {
                    PrintWriter clientOutput = new PrintWriter(client.getOutputStream(), true);
                    clientOutput.println(message);
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
    }
}
