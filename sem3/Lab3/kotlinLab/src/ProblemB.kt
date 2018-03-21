import java.io.BufferedWriter
import java.io.OutputStreamWriter
import java.io.PrintWriter
import java.util.*
import kotlin.collections.ArrayList

fun main(args: Array<String>) {
    var s = readLine()
    var ans = IntArray(s!!.length)
    val pw = PrintWriter(System.out)
    ans[0] = 0;
    pw.print("0 ")
    //pw.flush()
    for (i in 1..(s!!.length - 1)) {
        var k = ans[i - 1]
        while (k > 0 && s[k] != s[i]) {
            k = ans[k - 1]
        }
        if (s[i] == s[k]) {
            k++
        }
        ans[i] = k
        pw.print(k.toString() + " ")
        //pw.flush()
    }
    pw.close()
    //pw.flush()
    //for (i in 0..ans.size - 1) print("${ans[i]} ")
}