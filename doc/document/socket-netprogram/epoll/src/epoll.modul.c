
while (TRUE)
{
	int nfds = epoll_wait (m_epoll_fd, m_events, MAX_EVENTS, EPOLL_TIME_OUT);//等待EPOLL时间的发生，相当于监听，
	//至于相关的端口，需要在初始化EPOLL的时候绑定。
	if (nfds <= 0)
		continue;
	m_bOnTimeChecking = FALSE;
	G_CurTime = time(NULL);
	for(i=0;i<nfds;++i)
	{
		try
		{
			if (m_events[i].data.fd == m_listen_http_fd)//如果新监测到一个HTTP用户连接到绑定的HTTP端口，
				//建立新的连接。由于我们新采用了SOCKET连接，所以基本没用。
			{
				OnAcceptHttpEpoll ();
			}
			else if (m_events[i].data.fd == m_listen_sock_fd)//如果新监测到一个SOCKET用户连接到了绑定的SOCKET端口，
				//建立新的连接。
			{
				OnAcceptSockEpoll ();
			}
			else if (m_events[i].events & EPOLLIN)//如果是已经连接的用户，并且收到数据，那么进行读入。
			{
				OnReadEpoll (i);
			}

			OnWriteEpoll (i);//查看当前的活动连接是否有需要写出的数据。
		}
		catch (int)
		{
			PRINTF ("CATCH捕获错误\n");
			continue;
		}
	}
	m_bOnTimeChecking = TRUE;
	OnTimer ();//进行一些定时的操作，主要就是删除一些短线用户等。
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
               if(events[n].data.fd == listener) { //如果是主socket的事件的话，则表示有新连接进入了，进行新连接的处理。
                   client = accept(listener, (struct sockaddr *) &local,
                                   &addrlen);
                   if(client < 0){
                       perror("accept");
                       continue;
                   }
                   setnonblocking(client); // 将新连接置于非阻塞模式
                   ev.events = EPOLLIN | EPOLLET; // 并且将新连接也加入EPOLL的监听队列。注意，这里的参数EPOLLIN | EPOLLET并没有设置对写socket的监听，如果有写操作的话，这个时候epoll是不会返回事件的，如果要对写操作也监听的话，应该是EPOLLIN | EPOLLOUT | EPOLLET
                   ev.data.fd = client;
                   if (epoll_ctl(kdpfd, EPOLL_CTL_ADD, client, &ev) < 0) {
//  设置好event之后，将这个新的event通过epoll_ctl加入到epoll的监听队列里面，这里用EPOLL_CTL_ADD来加一个新的 epoll事件，通过EPOLL_CTL_DEL来减少一个epoll事件，通过EPOLL_CTL_MOD来改变一个事件的监听方式。
                       fprintf(stderr, "epoll set insertion error: fd=%d",  client);
                       return -1;
                   }
               }
               else // 如果不是主socket的事件的话，则代表是一个用户socket的事件，则来处理这个用户socket的事情，比如说read(fd,xxx)之类的，或者一些其他的处理。
                   do_use_fd(events[n].data.fd);
}