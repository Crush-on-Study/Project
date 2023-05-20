package chatting;

import java.io.*;
import java.net.*;
import java.util.Scanner;

public class Client {
    public static void main(String[] args) {
        try {
            // 서버에 연결
            Socket socket = new Socket("localhost", 12345);
            System.out.println("서버에 연결되었습니다.");

            // 입력 스트림 생성
            BufferedReader input = new BufferedReader(new InputStreamReader(socket.getInputStream()));

            // 출력 스트림 생성
            PrintWriter output = new PrintWriter(socket.getOutputStream(), true);

            // 사용자 입력을 받기 위한 스캐너 생성
            Scanner scanner = new Scanner(System.in);

            // 사용자명 입력 받기
            System.out.print("사용자명을 입력하세요: ");
            String username = scanner.nextLine();

            // 서버로 사용자명 전송
            output.println(username);

            // 메시지 수신을 위한 스레드 생성
            Thread receiveThread = new Thread(new ReceiveThread(input));
            receiveThread.start();

            // 사용자 입력 처리
            while (true) {
                String message = scanner.nextLine();

                // 입력한 메시지 서버로 전송
                output.println(message);

                // 종료 조건 확인
                if (message.equals("bye")) {
                    break;
                }
            }

            // 클라이언트 종료
            socket.close();
            scanner.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    // 메시지 수신 스레드
    static class ReceiveThread implements Runnable {
        private BufferedReader input;

        public ReceiveThread(BufferedReader input) {
            this.input = input;
        }

        @Override
        public void run() {
            try {
                String message;
                while ((message = input.readLine()) != null) {
                    System.out.println(message);
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
}
