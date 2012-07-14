
while (TRUE)
{
	int nfds = epoll_wait (m_epoll_fd, m_events, MAX_EVENTS, EPOLL_TIME_OUT);//�ȴ�EPOLLʱ��ķ������൱�ڼ�����
	//������صĶ˿ڣ���Ҫ�ڳ�ʼ��EPOLL��ʱ��󶨡�
	if (nfds <= 0)
		continue;
	m_bOnTimeChecking = FALSE;
	G_CurTime = time(NULL);
	for(i=0;i<nfds;++i)
	{
		try
		{
			if (m_events[i].data.fd == m_listen_http_fd)//����¼�⵽һ��HTTP�û����ӵ��󶨵�HTTP�˿ڣ�
				//�����µ����ӡ����������²�����SOCKET���ӣ����Ի���û�á�
			{
				OnAcceptHttpEpoll ();
			}
			else if (m_events[i].data.fd == m_listen_sock_fd)//����¼�⵽һ��SOCKET�û����ӵ��˰󶨵�SOCKET�˿ڣ�
				//�����µ����ӡ�
			{
				OnAcceptSockEpoll ();
			}
			else if (m_events[i].events & EPOLLIN)//������Ѿ����ӵ��û��������յ����ݣ���ô���ж��롣
			{
				OnReadEpoll (i);
			}

			OnWriteEpoll (i);//�鿴��ǰ�Ļ�����Ƿ�����Ҫд�������ݡ�
		}
		catch (int)
		{
			PRINTF ("CATCH�������\n");
			continue;
		}
	}
	m_bOnTimeChecking = TRUE;
	OnTimer ();//����һЩ��ʱ�Ĳ�������Ҫ����ɾ��һЩ�����û��ȡ�
}







//*************************

void setnonblocking(int sock)
{
    int opts;
    opts=fcntl(sock,F_GETFL);
    if(opts<0)
    {
        perror("fcntl(sock,GETFL)");
        exit(1);
    }
    opts = opts|O_NONBLOCK;
    if(fcntl(sock,F_SETFL,opts)<0)
    {
        perror("fcntl(sock,SETFL,opts)");
        exit(1);
    }
}



for(n = 0; n < nfds; ++n) {
               if(events[n].data.fd == listener) { //�������socket���¼��Ļ������ʾ�������ӽ����ˣ����������ӵĴ���
                   client = accept(listener, (struct sockaddr *) &local,
                                   &addrlen);
                   if(client < 0){
                       perror("accept");
                       continue;
                   }
                   setnonblocking(client); // �����������ڷ�����ģʽ
                   ev.events = EPOLLIN | EPOLLET; // ���ҽ�������Ҳ����EPOLL�ļ������С�ע�⣬����Ĳ���EPOLLIN | EPOLLET��û�����ö�дsocket�ļ����������д�����Ļ������ʱ��epoll�ǲ��᷵���¼��ģ����Ҫ��д����Ҳ�����Ļ���Ӧ����EPOLLIN | EPOLLOUT | EPOLLET
                   ev.data.fd = client;
                   if (epoll_ctl(kdpfd, EPOLL_CTL_ADD, client, &ev) < 0) {
//  ���ú�event֮�󣬽�����µ�eventͨ��epoll_ctl���뵽epoll�ļ����������棬������EPOLL_CTL_ADD����һ���µ� epoll�¼���ͨ��EPOLL_CTL_DEL������һ��epoll�¼���ͨ��EPOLL_CTL_MOD���ı�һ���¼��ļ�����ʽ��
                       fprintf(stderr, "epoll set insertion error: fd=%d",  client);
                       return -1;
                   }
               }
               else // ���������socket���¼��Ļ����������һ���û�socket���¼���������������û�socket�����飬����˵read(fd,xxx)֮��ģ�����һЩ�����Ĵ���
                   do_use_fd(events[n].data.fd);
}