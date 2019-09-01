### CBA Runtime Library Jornal

Like all my project, I will be keeping a journal of my work and my progress.  Once again, this file is more related to my thinking and my internal debated than it is about how the system/code is configured.  Decisions documented here will change.  Please be prepared for that.

---

## v0.0.0 -- Basic setup and project

# 2019-Aug-30

Today I was able to get a proper Gitpod up and running with everything I need to perform this work.  Having working through all the issues, I have committed this version and merged it into the master repo.

This merge was important because I actually did this as a pull request just to see what the basic process was from the repo owner perspective.  This was a first for me.  I also need to figure out how to comment on the code as a review.  Maybe I will remember in the next pull request.

---

## v0.0.1 -- Connection singleton

This version establish an interface for a connection to a CBA database.  This will be implemented using a singleton pattern.

# 2019-Aug-30

There may be a need down the road to support several schemas distributed over several servers.  Well, I only hope to be that successful.  For now, only 1 connection to a single datbase will be supported for all Schema objects.  Therefore, I only need a singleton class.

You know, I started a bit of this on codenvy.io and realized the limitations there.  I will be harvesting code from that cloud system to bring over here before I delete my account.  There are some initial problem -- which need to be sorted out, of course.  That will be for next time.


# 2019-Sep-01

OK, so I am startng with sorting out the compile issues.

The issue at hand is:

```
make: *** No rule to make target 'cba-session.o', needed by 'lib/libcba.a'.  Stop.
```

However, in the `Makefile` I have:

```
obj/%.o: src/%.cc
	mkdir -p obj
	$(CC) $(CFLAGS) -o $@ $<
```

..., and that should cover the build of the file.  God, I hate `make`.

---

I have this worked out.  I also have a test that is written to confirm that this is working.  This test will execute automatically on the build, allowing me to keep track of what is working and what is not.

I think I am ready for a commit.  Now, I want to be able to run the tests on demand and not with every build.  So, to test out the commit process, I am going to make some comments in the pull request to clean this piece up.

