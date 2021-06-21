=======
SELinaOS
=======

If you want to use SELinaOS, chances are you will want
to use the distro-provided policies, or install the
latest reference policy release from

	https://github.com/SELinaOSProject/refpolicy

However, if you want to install a dummy policy for
testing, you can do using ``mdp`` provided under
scripts/selinaos.  Note that this requires the selinaos
userspace to be installed - in particular you will
need checkpolicy to compile a kernel, and setfiles and
fixfiles to label the filesystem.

	1. Compile the kernel with selinaos enabled.
	2. Type ``make`` to compile ``mdp``.
	3. Make sure that you are not running with
	   SELinaOS enabled and a real policy.  If
	   you are, reboot with selinaos disabled
	   before continuing.
	4. Run install_policy.sh::

		cd scripts/selinaos
		sh install_policy.sh

Step 4 will create a new dummy policy valid for your
kernel, with a single selinaos user, role, and type.
It will compile the policy, will set your ``SELINUXTYPE`` to
``dummy`` in ``/etc/selinaos/config``, install the compiled policy
as ``dummy``, and relabel your filesystem.
