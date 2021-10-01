package com.company;

import java.util.Scanner;

public class Main {

    static int number[] = new int[100];

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        String ticket = sc.next();
        int len = ticket.length();

        int i;

        for(i=0; i<len; i++) {
            number[i] = Character.getNumericValue(ticket.charAt(i));
        }

        int maxLength = len%2==0 ? len : len-1;

        while(true) {
            boolean check = false;
            for(i=0; i<=len-maxLength; i++) {
                if(compare(i, maxLength/2)) {
                    check = true;
                    break;
                }
            }

            if(check) break;
            maxLength -= 2;
            if(maxLength == 0) break;
        }

        System.out.println(maxLength);
    }

    private static boolean compare(int start, int len) {
        int sumFirst = 0;
        int sumSecond = 0;

        for(int i=start; i<start+len; i++) {
            sumFirst += number[i];
            sumSecond += number[i+len];
        }

        if(sumFirst == sumSecond) return true;
        return false;
    }
}
