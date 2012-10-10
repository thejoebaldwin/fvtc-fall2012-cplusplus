Public Class Form1

    Private Sub Form1_Load(sender As System.Object, e As System.EventArgs) Handles MyBase.Load

    End Sub



    Private Function convertKilometers(ByRef dblMiles As Double)

        dblMiles = dblMiles * 1.26
        Return dblMiles

    End Function


End Class
