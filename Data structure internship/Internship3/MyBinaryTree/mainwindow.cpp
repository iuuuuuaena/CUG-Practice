�����ّ�+�E�3���[X;6�f⪽��^DSA}��D�#v�����P>�e���O4
�G.��v��>ʐW,>��i┽N��Z�{�M����5��-���A��NGu���s1�W�2�U������E�hy�������������g%�+DsH%���B�q�$o[�Y�"m������K47WS���pD$3���`���4 XN��|c���N�iw}f�*8�B���z0�HĊ�獋ʧ$���+�L[5��.��`Y�:�!�d�m�-�]�9���]�y������n�c$���wY@{`#$�E�s$%��;Kawi���W��@`0(�Hd6�V�~� P<
��,R������pH$-[~�`T(?^�8l�Ƚ���4|���T|�`p�e�{F�j�*�S4ZjX�#�ɚ0^�JT6��!~�SL=���`�����Cq�$V�~�`Oh4�I���r�啋/'\��2�U��(p�I{D�r�Q��!�H^��s=�ыg7��4��>tZ�{.�\y���ɑ��n��U��%� Xz��!��rڥ� ��}�!��a��>�}"�٣����A��ht�^z���ٖ�.@8X����Z��C�*��D�r�5H�*�_
�1����8|�͸V��5�4�Dn��~����#:��*���
�"�Ӷ�� Ɓ�\y�-捊����Gr��x�;%SZ����Tc�h@.�t	�Fʲ�5��(n��h}xe�	�F�2�Y�;���I������ц�b����?G54%WZ�;qqTe�k@7@p����1ڦ[;{��=���d�z>�b@(0ΗKoD�2�Ձ� k.��g)��(T��/96��N�tQ�|J��8F������-��4�VϺ�"_(
қ-�ݽ�����G` ��� $*^�xgb���>�D3E������TH?v�&�͇2��.�wI����އ�a��k>��v}!��\Z�0���lL�	4"�B�,��l�l]-"͂硋8��꽽1��$D(�_5eArray ba=str.toLatin1();
    char *c=ba.data();
    tree->CreatebyLevel(c);
    QMessageBox::information(this,"succeed","创建树成功.","ok");
}

void MainWindow::on_btn_find_clicked()
{
    if(!tree){
        QMessageBox::warning(this,"error","请先创建树..","ok");
    }
    QString str=this->ui->le3->text();
    if(str.isEmpty()){
        QMessageBox::warning(this,"error","请先输入要查找的节点..","ok");
    }
    char c=str.toStdString()[0];
    QString res;res=str+"的祖先节点:"+'\n';
    if(tree->Find(c,res)==NULL){
        res="所创建的树中没有该节点";
    }
    this->ui->textBrowser->setText(res);
}

void MainWindow::on_btn_cg_clicked()
{
    QString str1=this->ui->le1->text();
    QString str2=this->ui->le2->text();
    if(str1.isEmpty()){qDebug()<<"str1 is empty";}
    if(str2.isEmpty()){qDebug()<<"str2 is empty";}
    if(str1.length()!=str2.length()){qDebug()<<"str1 != str2";}
    if(str1.isEmpty()||str2.isEmpty()||str1.length()!=str2.len�+���ّ�7+�E�3%��Hv�f�ɿ��SC}��Hcv����75�όe�+�O4
�B.��u��>�z,<��i4n�����{�������җ/����j��NGu�w���1!��O�0�U��9���E��9�����-������g%�+AsH%�����q�$o[�/o�-��酾�K47Wc��rD$3+��`� N�4`h��|ca��NδTwf�*����z��M�Ɗ�����&���.�LX5��s ��bY�:.�m�}�m�]�9���]פ�����!^�c$����@9pd=� �q$%�[{K`wi���W��@���`�Hd6�V�~� P<
��,R������pH$f-W�>� <?^�8l��`ձ�4|A�T|�`p($�Hkv�f�*��X9��#�ɚ���HT6����SL=�ч̑<����Cq�$V�~�`Oh4J!]n��B�ᕋ/'\���U��(p>~H{D�r���!�Xn��s=�ыgH��6��N�4Z�{.�b�m��ɑ��n��k#k� Xz��!��rڥ�S�R_=�a¨a��>�(�b�ۣ��ؗA��ht.�\z��2�Ֆ�.�Z��&�Z��CI���F�r���8��_
�2���֋��͸U��5�4�Dn�����M���:��*���ת�"����� �