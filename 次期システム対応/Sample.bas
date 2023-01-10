

Private Function Error2CaruteUpdate(ByRef UpdFlg As Boolean) As Boolean
    
    Dim SQLCmd As String
    
    Error2CaruteUpdate = True
     
    SQLCmd = "DELETE from BNP_Temp WHERE udate = #" & Trim(Err2Form.TxCurUdate.Value) & "# and ino = '" & Trim(Err2Form.TxCurIno.Value) & "'"
    Ret = ExecSQLCmd(SQLCmd)
    If Ret = False Then
        Error2CaruteUpdate = False
    End If

End Function

Private Function ExecSQLCmd(ByVal SqlCommand As String) As Boolean

    Dim adoCmd As ADODB.Command
    Dim sWork As String
    
    On Error GoTo SQLCMDErr2
    
    ExecSQLCmd = True
    Set adoCmd = New ADODB.Command
    
    sWork = "SQL実行[" & SqlCommand & "]"
    'msgbox sWork
    
    With adoCmd
        .ActiveConnection = adoCn
        .CommandText = SqlCommand
        .Execute
    End With
    
    Set adoCmd = Nothing

    Exit Function
    
SQLCMDErr2:
    Dim ErrLoop As Integer

    'エラーメッセージ出力
    If adoCn.Errors.Count > 0 Then
        For ErrLoop = 0 To adoCn.Errors.Count - 1
            sWork = "SQL Error Message [" & adoCn.Errors(ErrLoop).Description & "]"
	        msgbox sWork
            sWork = "SQLSTATE: " & adoCn.Errors(ErrLoop).SqlState
	        msgbox sWork
        Next
        adoCn.Errors.Clear
    Else
        sWork = "Error Message [" & Err.Description & "]"
        msgbox sWork
        Err.Clear
    End If
    
    ExecSQLCmd = False
    
    On Error GoTo 0
    
End Function
