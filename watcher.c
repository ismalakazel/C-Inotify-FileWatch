#include <stdlib.h>
#include <sys/inotify.h>
#include <errno.h>
#include <stdio.h>
#include <poll.h>
#include <unistd.h>
#include <string.h>

/// Use inotify API to monitor changes in a file.
///
/// (inotify)[https://man7.org/linux/man-pages/man7/inotify.7.html]
///
/// - Parameter argc: argv count.
/// - Parameter *argv: The file path that needs to be monitored.
int main(int argc, char *argv[]) {

  printf("File path: %s \n", argv[1]);

  /// Watch for events in path.
  const char *path = argv[1];
  const int fd = inotify_init();
  const int wd = inotify_add_watch(fd, path, IN_ALL_EVENTS);

  if (wd == -1) {
    perror("wd");
    exit(EXIT_FAILURE);
  }

  /// Create a set of fd to be monitored.
  struct pollfd pfds[1];
  struct pollfd pfd; 
  pfd.fd = fd;
  pfd.events = POLLIN;
  pfds[0] = pfd;

  /// Start polling for events.
  while(1) {
    const int nfiles = 1; 
    const int POLL_ERROR = -1;
    const int POLL_EVENT_AVAILABLE = 1;
    const int POLL_TIMEOUT = -1;
    int rpoll = poll(pfds, nfiles, POLL_TIMEOUT);

    if (rpoll == POLL_ERROR) {
      perror("Poll");
      exit(EXIT_FAILURE);
    };

    if (rpoll == POLL_EVENT_AVAILABLE) {
      if (pfds[0].revents & POLLIN) {
        int BUFFER_SIZE = 1024 * sizeof(struct inotify_event);
        char buffer[BUFFER_SIZE]; 
        read(fd, buffer, BUFFER_SIZE);
        struct inotify_event *event = (struct inotify_event *) &buffer[0];
        if (event->mask & IN_MODIFY)
          printf("File modified \n");
      }
    }
  }
  
  close(fd);
  exit(EXIT_SUCCESS);
}
