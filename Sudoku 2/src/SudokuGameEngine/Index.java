package SudokuGameEngine;

import java.io.Serializable;

public class Index implements Serializable {

    public final int i;
    public final int j;

    public Index(final int first, final int second) {
        i = first;
        j = second;
    }
}